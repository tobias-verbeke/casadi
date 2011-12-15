from casadi import *
from casadi.tools import *
from pylab import *
import numpy as np
import matplotlib
matplotlib.interactive(True)

ion()

# Solving the following estimation problem:
#
# min_{X,V,q}  || X - X_ref ||^2_2
#
#   s.t.   dX = V
#          dV = R * a^hat
#          dq = 1/2 * G * w^hat
#
# Pitfalls: NLP might converge to quaternions (0,0,0,0), an invalid solution where x(t) is a straight line, R being zero.
#           Initializing with (0,0,0,1) seems to fix this

havePlots = True

nk = 100   # Number of imu measurements/collocation intervals
tf = 2    # End time [s]

states  = Variables()  # Collect the states
dstates = Variables()  # Collect the derivatives of the states

t = SX("t") # time

# states related to position
states.X   = ssym("p",3)    # In inertial frame
dstates.X  = ssym("dp",3)   # In inertial frame

# states related to velocity
states.V   = ssym("v",3)    # In inertial frame
dstates.V  = ssym("dv",3)   # In inertial frame

# states related to orientation
states.q   = ssym("q",4)             
dstates.q  = ssym("dq",4)

q0,q1,q2,q3 = states.q

# Helper variables to get to quaternions
def skew(vec):
  x,y,z = vec
  return SXMatrix([[0,-z,y],[z,0,-x],[-y,x,0]])
  
rho = states.q[:3]
rho_skew = skew(rho)

# Transformation: p_world = R * p_body
R = (SXMatrix.eye(3)*(mul(rho.T,-rho)+q3*q3)+mul(rho,rho.T)*2.0-q3*rho_skew*2.0).T

# Quaternion dynamic matrix
G = numpy.matrix([[q3,-q2,q1],[q2,q3,-q0],[-q1,q0,q3],[-q0,-q1,-q2]])

imu = Variables()       # Collect the quantities that the imu measures
imu.a = ssym("a^hat",3) # Measured linear acceleration in body frame
imu.w = ssym("w^hat",3) # Measured angular rate in body frame

rhs = [0] * 3  # The right hand side will have three parts

rhs[states.I_X] = states.V - dstates.X 
rhs[states.I_V] = mul(R,imu.a) - dstates.V
rhs[states.I_q] = 0.5*mul(G,imu.w) - dstates.q

# This is our DAE
dae = SXFunction({'NUM':DAE_NUM_IN, DAE_T: t, DAE_Y: states.veccat(), DAE_YDOT: dstates.veccat(), DAE_P: imu.veccat()},[vertcat(rhs)])

# Let's generate some dummy measurements
# First, we need dummy excitations.
ts = numpy.linspace(0,tf,nk+1)
tsm = ts[:-1]

sim = ControlSimulator(dae,ts)
sim.setOption("integrator",CVodesIntegrator)
sim.setOption("np",0)   # There are no fixed parameters
sim.setOption("nf",10)  # Evaluate the integral nf times in each interval
sim.init()

states.X_ = states.V_ = [0,0,0]  # Initial state to generate the dummy measurements
states.q_ = [0,0,0,1]            

sim.input(CONTROLSIMULATOR_X0).set(states.veccat_())
sim.input(CONTROLSIMULATOR_V)[:,imu.i_a.T] = DMatrix([sin(tsm),cos(3*tsm),sin(2*tsm)]).T
sim.input(CONTROLSIMULATOR_V)[:,imu.i_w.T] = DMatrix([cos(3*tsm),sin(7*tsm),sin(11*tsm)]).T

sim.evaluate()

tsf = sim.getGrid()  # The fine time grid of the controlsimulator

reference_imu = sim.input(CONTROLSIMULATOR_V)
reference_Xf   = sim.output()[:,states.i_X.T]

reference_X   = reference_Xf[sim.getCoarseIndex(),:]

Rf = SXFunction([states.q],[vec(R)])
Rf.init()
reference_Rf = numSample1D(Rf,sim.output()[:,states.i_q.T].T).T
reference_R   = reference_Rf[sim.getCoarseIndex(),:]
# End of generating dummy excitations

# Formulate the estimation problem using a collocation approach

# Choose collocation points
tau_root = [0,0.155051,0.644949,1.000000]

# Degree of interpolating polynomial + 1
d = len(tau_root)

tau = SX("tau")

# A vertical stack of d-by-1 Langrange functions that together form a basis on the collocation interval tau = [0..1]
Le = vertcat([numpy.prod([(tau - tau_root[r])/(tau_root[j]-tau_root[r]) for r in range(d) if not(r==j)]) for j in range(d)])
L = SXFunction([tau],[Le])
L.init()
dL = L.jacobian(0,0)
dL.init()


# Show the lagrange basis for didactic purposes
x = DMatrix([2,-1,4,3]) # some random numbers

xp = SXFunction([tau],[ mul(x.T,Le), mul(x.T,dL.eval([tau])[0]) ])
xp.init()
taus = DMatrix(numpy.linspace(0,1,500)).T
    
L.input().set(1)
L.evaluate()
Lend = DMatrix(L.output())  # Le at the end of the control interval

dLm = numSample1D(dL,DMatrix(tau_root).T)  # d-by-d

optvar = Variables()  # Decision variables we optimize for

X   = optvar.X   = [ ssym("X", states.shape[0],d) for i in range(nk+1) ]

par = Variables()  # Fixed parameters for the nlp
par.IMU   = ssym("imu",reference_imu.shape)  # IMU measurements
par.Xref  = ssym("Xref",reference_X.shape)  # Reference measurements
par.IMU_  = reference_imu 
par.Xref_ = reference_X  

hk = (tf+0.0)/nk  # The time duration of a collocation interval

g   = [] # Collect the equality constraints
tsc = [] # Physical time at collocation points

for k,tk in enumerate(ts[:-1]):
  dX = mul(optvar.X[k],dLm)/hk
  if k+1 < nk:   #  Constraint coupling state at end of k and start of k+1
    g.append(optvar.X[k+1][:,0]-mul(optvar.X[k],Lend)) 
  tsc.append(tk)
  for j in range(1,d):
    tsc.append(tk + hk * tau_root[j])  # The physical time
    [dyn] = dae.eval({'NUM':DAE_NUM_IN,
                DAE_T:    tsc[-1],
                DAE_Y:    optvar.X[k][:,j],
                DAE_YDOT: dX[:,j],
                DAE_P:    par.IMU[k,:]})
    g.append(dyn)   
    
g.append(sumRows(optvar.X[0][states.i_q,0]**2) - 1)  # Add the quaternion norm constraint at the start

g = SXFunction([optvar.veccat(),par.veccat()],[vertcat(g)])
g.init()

J = g.jac(0,0)

# Objective function
f = sumAll( (horzcat([i[states.i_X,0] for i in optvar.X]).T -par.Xref)**2 )
f = SXFunction([optvar.veccat(),par.veccat()],[f])
f.init()

class NLPSolutionInspector:
  def __init__(self):
    self.iter = 0 
    self.log= numpy.zeros((4,1000))
    self.colors = list("bgrcmyk"*5)
    figure(2,figsize=(14,10))
    subplot(311)
    title('X(t)')

    for i in range(reference_Xf.shape[1]):
      plot(tsf,reference_Xf[:,i],':'+self.colors[i])
    plot(ts,reference_X,'k|')
    subplot(312)
    title('R(t)')
    
    for i in range(reference_Rf.shape[1]):
      plot(tsf,reference_Rf[:,i],':'+self.colors[i])
    plot(ts,reference_R,'k|')
    self.i = 0
    
  def __call__(self,f,*args):
    if self.i>0:
      self.log[0,self.i] = log10(f.getStats()['inf_pr'])
      self.log[1,self.i] = log10(f.getStats()['inf_du'])
      self.log[2,self.i] = float(log10(f.input(NLP_COST)))
      self.log[3,self.i] = f.getStats()['ls_trials']
      
    self.i += 1
    sol = f.input(NLP_X_OPT)
    X_opt = horzcat([sol[i][states.i_X,:] for i in optvar.i_X])
    q_opt = horzcat([sol[i][states.i_q,:] for i in optvar.i_X])
    R_opt = numSample1D(Rf,q_opt)
    
    if hasattr(self,'xlines'):
        for i in range(3):
            self.xlines[i].set_ydata(X_opt[i,:-d].T)
        for i in range(R_opt.shape[0]):   
            self.rlines[i].set_ydata(R_opt[i,:-d].T)
    else:
        subplot(311)
        self.xlines = []
        self.rlines = []
        for i in range(reference_Xf.shape[1]):
          self.xlines.append(plot(tsc,X_opt[i,:-d].T,'-'+self.colors[i])[0])
        subplot(312)
        for i in range(reference_Rf.shape[1]):
          self.rlines.append(plot(tsc,R_opt[i,:-d].T,'-'+self.colors[i])[0])
        
    if hasattr(self,'obj'):
        for i in range(4):
            self.obj[i].set_ydata(self.log[i,1:self.i])
            self.obj[i].set_xdata(range(self.i-1))
        subplot(313).relim()
        subplot(313).autoscale_view()
    else:
        subplot(313)
        title('convergence behaviour')
        
        self.obj = [plot([1],'-')[0] for i in range(4)]
        legend(['pr','du','obj','ls'],loc='center left', bbox_to_anchor=(1, 0.5))
    draw()
    
      
iterationInspector = NLPSolutionInspector()

nlp = IpoptSolver(f,g)
nlp.init()

 #! We wrap the logging instance in a PyFunction
c = PyFunction( iterationInspector, [ nlp.output(NLP_X_OPT).sparsity() ,nlp.output(NLP_COST).sparsity() , nlp.output(NLP_LAMBDA_G).sparsity() , nlp.output(NLP_LAMBDA_X).sparsity() ], [sp_dense(1,1)] )
c.init()
nlp.setOption("iteration_callback",c)
nlp.setOption('tol',1e-8)
nlp.init()

nlp.solve()
for i in range(nk+1):  # intialize with (0,0,0,1) quaternion
  nlp.input(NLP_X_INIT)[optvar.i_X[i][states.i_q[3],:]] = 1
nlp.input(NLP_P).set(par.veccat_())
nlp.input(NLP_LBG).setAll(0)
nlp.input(NLP_UBG).setAll(0)
nlp.solve()

sol = nlp.output()

X_opt = horzcat([sol[i][states.i_X,:] for i in optvar.i_X])

show()