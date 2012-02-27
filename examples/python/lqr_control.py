from pylab import *
from casadi import *
from casadi.tools import Variables
import scipy.linalg
import numpy as np

"""
This example how an Linear Quadratic Regulator (LQR) can be designed
and simulated for a linear-time-invariant (LTI) system
"""

# Problem statement
# -----------------------------------

# System dimensions
ns = 3  # number of states
nu = 2  # number of controls
ny = 2  # number of outputs
N  = 20 # number of control intervals
te = 10 # end time [s]

# The system equations:   x' = A.x + B.u
A = DMatrix([[0.4,0.1,-2],[0,-0.3,4],[1,0,0]])
B = DMatrix([[1,1],[0,1],[1,0]])

# Inspect the open-loop system
[D,V] = linalg.eig(A)
print "Open-loop eigenvalues: ", D

tn = linspace(0,te,N)

# Check if the system is controllable
# -----------------------------------
R = []

p = B
for i in range(ns):
  R.append(p)
  p = mul([A,p])
  
R = horzcat(R)

# R must be of full rank
_, s, _ = linalg.svd(R)
eps = 1e-9
rank =  len([x for x in s if abs(x) > eps])
assert(rank==ns)

# Simulation of the open-loop system
# -----------------------------------

y  = ssym("y",ns)
dy  = ssym("dy",ns)
u  = ssym("u",nu)

x0 = DMatrix([1,0,0])
# no control
u_ = DMatrix([[ 0, 0 ]]*(N-1))

p = SX("p")

tn = np.linspace(0,te,N)
cdae = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: y,  CONTROL_DAE_YDOT: dy, CONTROL_DAE_U: u},[mul(A,y)+mul(B,u)])
cdae.init()


sim = ControlSimulator(cdae,tn)
sim.setOption("integrator", CVodesIntegrator)
sim.setOption("integrator_options", {"fsens_err_con": True,"reltol":1e-12})
sim.setOption("nf",20)
sim.init()
sim.setInput(x0,CONTROLSIMULATOR_X0)
sim.setInput(u_,CONTROLSIMULATOR_U)
sim.evaluate()

tf = sim.getMinorT()

figure(1)
plot(tf,sim.output())
legend(('s1', 's2','s3'))
title('reference simulation, open-loop, zero controls')
out = DMatrix(sim.output())

# Simulation of the open-loop system
#   sensitivity for initial conditions
# -----------------------------------

x0_pert = DMatrix([0,0,1])*1e-4
sim.setInput(x0+x0_pert,CONTROLSIMULATOR_X0)
sim.setInput(u_,CONTROLSIMULATOR_U)
sim.evaluate()

tf = list(sim.getMinorT())

figure(2)
title('Deviation from reference simulation, with perturbed initial condition')
plot(tf,sim.output()-out,linewidth=3)

jacsim = Jacobian(sim,CONTROLSIMULATOR_X0,0)
jacsim.init()
jacsim.setInput(x0,CONTROLSIMULATOR_X0)
jacsim.setInput(u_,CONTROLSIMULATOR_U)

jacsim.evaluate()

dev_est = []
for i in range(len(tf)):
  dev_est.append(mul(jacsim.output()[i*ns:(i+1)*ns,:],x0_pert))

dev_est = horzcat(dev_est).T
plot(tf,dev_est,'+k')
legend(('s1 dev', 's2 dev','s3 dev','s1 dev (est.)', 's2 dev (est.)','s3 dev (est.)'),loc='upper left')


M = jacsim.output()[-ns:,:]
# In the case of zero input, we could also use the matrix exponential to obtain sensitivity
Mref = scipy.linalg.expm(A*te)

e = fabs(M - Mref)
e = max(e)/max(fabs(M))
print e
assert(e<1e-6)

# Simulation of the open-loop system
#   sensitivity  for controls
# -----------------------------------
# What if we perturb the input?

u_perturb = DMatrix(u_)
u_perturb[N/5,0] = 1e-4
sim.setInput(x0,CONTROLSIMULATOR_X0)
sim.setInput(u_+u_perturb,CONTROLSIMULATOR_U)
sim.evaluate()

figure(3)
title('Deviation from reference simulation, with perturbed controls')
plot(tf,sim.output()-out,linewidth=3)



jacsim = Jacobian(sim,CONTROLSIMULATOR_U,0)
jacsim.init()
jacsim.setInput(x0,CONTROLSIMULATOR_X0)
jacsim.setInput(u_,CONTROLSIMULATOR_U)

jacsim.evaluate()

dev_est = []
for i in range(len(tf)):
  dev_est.append(mul(jacsim.output()[i*ns:(i+1)*ns,:],flatten(u_perturb)))

dev_est = horzcat(dev_est).T
plot(tf,dev_est,'+k')
legend(('s1 dev', 's2 dev','s3 dev','s1 dev (est.)', 's2 dev (est.)','s3 dev (est.)'),loc='upper left')


# Find feedforward controls
# -----------------------------------
#
#  Our goal is to reach a particular end-state xref_e
#  We can find the necessary controls explicitly in continuous time
#  with the controllability Gramian 
#  
#  http://www-control.eng.cam.ac.uk/jmm/3f2/handout4.pdf
#  http://www.ece.rutgers.edu/~gajic/psfiles/chap5.pdf

x0 = vertcat([1,0,0])
xref_e = vertcat([1,0,0])

states = Variables()
eAt = states.eAt = ssym("eAt",ns,ns) # The matrix exponential exp(A*t)
Wt  = states.Wt = ssym("Wt",ns,ns)   # The Gramian matrix
states.freeze()

# We will find the control that allow to reach xref_e at t1
t1 = te

# Initial conditions
e = DMatrix.eye(ns)
makeDense(e)
states.eAt_ = e
states.Wt_ = DMatrix.zeros((ns,ns))

rhs = Variables()
rhs.eAt = mul(A,eAt)
rhs.Wt  = mul([eAt,B,B.T,eAt.T])
rhs.freeze()

dae = SXFunction({'NUM':DAE_NUM_IN, DAE_Y: states.veccat()},[rhs.veccat()])
dae.init()

integrator = CVodesIntegrator(dae)
integrator.setOption("tf",t1)
integrator.setOption("reltol",1e-12)
integrator.init()
integrator.setInput(states.veccat_(),INTEGRATOR_X0)
integrator.evaluate()

Wt_  = integrator.output()[states.i_Wt]
eAt_ = integrator.output()[states.i_eAt]

# Check that eAt is indeed the matrix exponential
e = max(fabs(eAt_-scipy.linalg.expm(A*te)))/max(fabs(eAt_))
assert(e<1e-7)

# Simulate with feedforward controls
# -----------------------------------

states = Variables()
states.y = y # The regular states of the LTI system
eAt = states.eAt = ssym("eAt",ns,ns) # The matrix exponential exp(A*(t1-t))
states.freeze()

# Initial conditions
states.y_ = x0
states.eAt_ = eAt_

u = mul([B.T,eAt.T,inv(Wt_),xref_e-mul(eAt_,x0)])

rhs = Variables()
rhs.y   = mul(A,y)+mul(B,u)
rhs.eAt = -mul(A,eAt)
rhs.freeze()

cdae = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: states.veccat(), CONTROL_DAE_YDOT: ssym("dy",states.shape)},[rhs.veccat()])
cdae.init()

# Output function
out = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: states.veccat(), CONTROL_DAE_YDOT: ssym("dy",states.shape)},[states.veccat(),u])
out.init()

sim = ControlSimulator(cdae,out,tn)
sim.setOption("integrator", CVodesIntegrator)
sim.setOption("integrator_options", {"fsens_err_con": True,"reltol":1e-12})
sim.setOption("nf",20)
sim.init()
sim.setInput(states.veccat_(),CONTROLSIMULATOR_X0)
sim.evaluate()
sim.output()

e = sim.output()[-1,states.i_y] - xref_e
assert(max(fabs(e))/max(fabs(xref_e))<1e-6)

tf = sim.getMinorT()
# This will be our reference trajectory for tracking

figure(4)
subplot(211)
title("Feedforward control, states")
plot(tf,sim.output(0)[:,list(states.i_y)])
for i,c in enumerate(['b','g','r']):
  plot(t1,xref_e[i],c+'o')
subplot(212)
title("Control action")
plot(tf,sim.output(1))

# Design an infinite horizon LQR
# -----------------------------------

# Weights for the infinite horizon LQR control
Q = DMatrix.eye(ns)
R = DMatrix.eye(nu)

# Continuous Riccati equation
P = ssym("P",ns,ns)

ric = (Q + mul(A.T,P) + mul(P,A) - mul([P,B,inv(R),B.T,P]))

dae = SXFunction({'NUM':DAE_NUM_IN, DAE_Y: flatten(P)},[ric])
dae.init()

# We solve the ricatti equation by simulating backwards in time until steady state is reached.
integrator = CVodesIntegrator(dae)
integrator.setOption("reltol",1e-16)
integrator.init()
integrator.reset(0,0)
# Start from P = identity matrix
u = DMatrix.eye(ns)
makeDense(u)
integrator.setInput(flatten(u),INTEGRATOR_X0)
integrator.integrate(0)

# Keep integrating until steady state is reached
for i in range(1,40):
  x0 = DMatrix(integrator.output())
  integrator.integrate(1*i)
  xe = DMatrix(integrator.output())
  e = max(fabs(xe-x0))
  print "it. %02d - deviation from steady state: %.2e" % (i, e)
  if e < 1e-11:
    break
  
# Obtain the solution of the ricatti equation
P_ = integrator.output().reshape((ns,ns))
print "P=", P_

# Check that it does indeed satisfy the ricatti equation
dae.setInput(integrator.output(),DAE_Y)
dae.evaluate()
assert(max(fabs(dae.output()))<1e-9)

# From P, obtain a feedback matrix K
K = mul([inv(R),B.T,P_])

print "feedback matrix= ", K

# Inspect closed-loop eigenvalues
[D,V] = linalg.eig(A-mul(B,K))
print "Open-loop eigenvalues: ", D

# Simulation of the closed-loop system:
#  continuous control action, various continuous references
# ---------------------------------------------------------
#

x0 = DMatrix([1,0,0])

y  = ssym("y",ns)
dy  = ssym("dy",ns)

C = DMatrix([[1,0,0],[0,1,0]])
D = DMatrix([[0,0],[0,0]])

temp = inv(blockcat([[A,B],[C,D]]))

F = temp[:ns,-ny:]
Nm = temp[ns:,-ny:]

t = SX("t")

figure(6)

for k,yref in enumerate([ vertcat([-1,sqrt(t)]) , vertcat([-1,-0.5]), vertcat([-1,sin(t)])]):
  u = -mul(K,y) + mul(mul(K,F)+Nm,yref)
  rhs = mul(A,y)+mul(B,u)
  cdae = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_T: t, CONTROL_DAE_Y: y,  CONTROL_DAE_YDOT: dy},[rhs])

  # Output function
  out = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_T: t, CONTROL_DAE_Y: y, CONTROL_DAE_YDOT: dy},[y,mul(C,y),u,yref])
  out.init()

  sim = ControlSimulator(cdae,out,tn)
  sim.setOption("integrator", CVodesIntegrator)
  sim.setOption("integrator_options", {"fsens_err_con": True,"reltol":1e-12})
  sim.setOption("nf",200)
  sim.init()
  sim.setInput(x0,CONTROLSIMULATOR_X0)
  #sim.setInput(yref_,CONTROLSIMULATOR_U)
  sim.evaluate()

  tf = sim.getMinorT()

  subplot(3,3,1+k*3)
  plot(tf,sim.output(0))
  subplot(3,3,2+k*3)
  title('ref ' + str(yref))
  for i,c in enumerate(['b','g']):
    plot(tf,sim.output(1)[:,i],c,linewidth=2)
    plot(tf,sim.output(3)[:,i],c+'-')
  subplot(3,3,3+k*3)
  plot(tf,sim.output(2))


# Simulation of the closed-loop system:
#  continuous control action, continuous feedforward reference
# -----------------------------------------------------------
#  To obtain a continous tracking reference,
#  we augment statespace to construct it on the fly

x0 = vertcat([1,0,0])

# Now simulate with open-loop controls
states = Variables()
states.y = y  = ssym("y",ns)    # The regular states of the LTI system
states.yref   = ssym("yref",ns) # States that constitute a tracking reference for the LTI system
states.eAt = eAt = ssym("eAt",ns,ns) # The matrix exponential exp(A*(t1-t))
states.freeze()

# Initial conditions
states.y_    = 2*x0
states.yref_ = x0
states.eAt_  = eAt_

param = Variables()
param.K = ssym("K",nu,ns)
param.freeze()

uref = mul([B.T,eAt.T,inv(Wt_),xref_e-mul(eAt_,x0)])
u    = uref - mul(param.K,y-states.yref)

rhs = Variables()
rhs.y      =  mul(A,y)+mul(B,u)
rhs.yref   =  mul(A,states.yref)+mul(B,uref)
rhs.eAt    = -mul(A,eAt)
rhs.freeze()

cdae = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: states.veccat(), CONTROL_DAE_YDOT: ssym("dy",states.shape), CONTROL_DAE_P: param.veccat()},[rhs.veccat()])
cdae.init()

# Output function
out = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: states.veccat(), CONTROL_DAE_YDOT: ssym("dy",states.shape), CONTROL_DAE_P: param.veccat()},[states.veccat(),u,uref,states.yref])
out.init()

sim = ControlSimulator(cdae,out,tn)
sim.setOption("integrator", CVodesIntegrator)
sim.setOption("integrator_options", {"fsens_err_con": True,"reltol":1e-8})
sim.setOption("nf",20)
sim.init()

jacsim = Jacobian(sim,CONTROLSIMULATOR_X0,0)
jacsim.init()

figure(7)
  
for k,(caption,K_) in enumerate([("K: zero",DMatrix.zeros((nu,ns))),("K: LQR",K)]):
  param.K_ = K_

  sim.setInput(states.veccat_(),CONTROLSIMULATOR_X0)
  sim.setInput(param.veccat_(),CONTROLSIMULATOR_P)
  sim.evaluate()
  sim.output()

  tf = sim.getMinorT()
  
  subplot(2,2,2*k+1)
  title('states (%s)' % caption)
  for i,c in enumerate(['b','g','r']):
    plot(tf,sim.output()[:,states.i_yref[i]],c+'--')
    plot(tf,sim.output()[:,states.i_y[i]],c,linewidth=2)
  subplot(2,2,2*k+2)
  for i,c in enumerate(['b','g']):
    plot(tf,sim.output(1)[:,i],c,linewidth=2)
    plot(tf,sim.output(2)[:,i],c+'--')
  title('controls (%s)' % caption)

  # Calculate monodromy matrix
  jacsim.setInput(states.veccat_(),CONTROLSIMULATOR_X0)
  jacsim.setInput(param.veccat_(),CONTROLSIMULATOR_P)
  jacsim.evaluate()
  M = jacsim.output()[-states.shape[0]:,:][list(states.i_y),list(states.i_y)]
  
  # Inspect the eigenvalues of M
  [D,V] = linalg.eig(M)
  print "Spectral radius of monodromy (%s): " % caption
  
  print max(abs(D))

print "Spectral radius of exp((A-BK)*te): "

[D,V] = linalg.eig(scipy.linalg.expm((A-mul(B,K))*te))
print max(abs(D))

# Simulation of the controller:
# discrete reference, continuous control action
# -----------------------------------------------------------

# Get discrete reference from previous simulation
mi = sim.getMajorIndex()
controls_ = sim.output(2)[mi[:-1],:]
yref_     = sim.output(3)[mi[:-1],:]

u_ = horzcat([controls_,yref_])

x0 = DMatrix([1,0,0])

controls = Variables()
controls.uref = ssym("uref",nu)
controls.yref = ssym("yref",ns)
controls.freeze()

yref  = ssym("yref",ns)
y     = ssym("y",ns)
dy    = ssym("dy",ns)
u     = controls.uref-mul(param.K,y-controls.yref)
rhs   = mul(A,y)+mul(B,u)

cdae = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: y,  CONTROL_DAE_YDOT: dy, CONTROL_DAE_U: controls.veccat(), CONTROL_DAE_P: param.veccat()},[rhs])

# Output function
out = SXFunction({'NUM':CONTROL_DAE_NUM_IN,  CONTROL_DAE_Y: y,  CONTROL_DAE_YDOT: dy, CONTROL_DAE_U: controls.veccat(), CONTROL_DAE_P: param.veccat()},[y,u,controls.uref,controls.yref])
out.init()

sim = ControlSimulator(cdae,out,tn)
sim.setOption("integrator", CVodesIntegrator)
sim.setOption("integrator_options", {"fsens_err_con": True,"reltol":1e-8})
sim.setOption("nf",20)
sim.init()
sim.setInput(2*x0,CONTROLSIMULATOR_X0)
sim.setInput(param.veccat_(),CONTROLSIMULATOR_P)
sim.setInput(u_,CONTROLSIMULATOR_U)
sim.evaluate()

tf = sim.getMinorT()

figure(8)
subplot(2,1,1)
title('states (%s)' % caption)
for i,c in enumerate(['b','g','r']):
  plot(tf,sim.output(3)[:,i],c+'--')
  plot(tf,sim.output()[:,i],c,linewidth=2)
subplot(2,1,2)
for i,c in enumerate(['b','g']):
  plot(tf,sim.output(1)[:,i],c,linewidth=2)
  plot(tf,sim.output(2)[:,i],c+'--')
title('controls (%s)' % caption)
  
jacsim = Jacobian(sim,CONTROLSIMULATOR_X0,0)
jacsim.init()

# Calculate monodromy matrix
jacsim.setInput(x0,CONTROLSIMULATOR_X0)
jacsim.setInput(param.veccat_(),CONTROLSIMULATOR_P)
jacsim.setInput(u_,CONTROLSIMULATOR_U)
jacsim.evaluate()
M = jacsim.output()[-ns:,:]

# Inspect the eigenvalues of M
[D,V] = linalg.eig(M)
print "Spectral radius of monodromy, discrete reference, continous control"

print max(abs(D))
  
# Simulation of the controller:
# discrete reference, discrete control action
# -----------------------------------------------------------

y0     = ssym("y0",ns)

u     = controls.uref-mul(param.K,y0-controls.yref)
rhs   = mul(A,y)+mul(B,u)

cdae = SXFunction({'NUM':CONTROL_DAE_NUM_IN, CONTROL_DAE_Y: y,  CONTROL_DAE_YDOT: dy, CONTROL_DAE_Y_MAJOR: y0, CONTROL_DAE_U: controls.veccat(), CONTROL_DAE_P: param.veccat()},[rhs])

# Output function
out = SXFunction({'NUM':CONTROL_DAE_NUM_IN,  CONTROL_DAE_Y: y,  CONTROL_DAE_YDOT: dy, CONTROL_DAE_Y_MAJOR: y0, CONTROL_DAE_U: controls.veccat(), CONTROL_DAE_P: param.veccat()},[y,u,controls.uref,controls.yref])
out.init()

sim = ControlSimulator(cdae,out,tn)
sim.setOption("integrator", CVodesIntegrator)
sim.setOption("integrator_options", {"fsens_err_con": True,"reltol":1e-8})
sim.setOption("nf",20)
sim.init()
sim.setInput(2*x0,CONTROLSIMULATOR_X0)
sim.setInput(param.veccat_(),CONTROLSIMULATOR_P)
sim.setInput(u_,CONTROLSIMULATOR_U)
sim.evaluate()

tf = sim.getMinorT()

figure(9)
subplot(2,1,1)
title('states (%s)' % caption)
for i,c in enumerate(['b','g','r']):
  plot(tf,sim.output(3)[:,i],c+'--')
  plot(tf,sim.output()[:,i],c,linewidth=2)
subplot(2,1,2)
for i,c in enumerate(['b','g']):
  plot(tf,sim.output(1)[:,i],c,linewidth=2)
  plot(tf,sim.output(2)[:,i],c+'--')
title('controls (%s)' % caption)

jacsim = Jacobian(sim,CONTROLSIMULATOR_X0,0)
jacsim.init()

# Calculate monodromy matrix
jacsim.setInput(x0,CONTROLSIMULATOR_X0)
jacsim.setInput(param.veccat_(),CONTROLSIMULATOR_P)
jacsim.setInput(u_,CONTROLSIMULATOR_U)
jacsim.evaluate()
M = jacsim.output()[-ns:,:]

# Inspect the eigenvalues of M
[D,V] = linalg.eig(M)
print "Spectral radius of monodromy, discrete reference, discrete control"

print max(abs(D))

show()