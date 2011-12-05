# -*- coding: utf-8 -*-
from casadi import *
import numpy as NP
import matplotlib.pyplot as plt

# This is a CasADi version of corkscrw.mod from the cute test collection, original by Hande Y. Benson
#   
#   Ph. Toint

#t=1000 #original
#t=5000 #web
t = 500 # cuter
xt = 10.0
mass = 0.37
tol = 0.1

h = xt/t
w = xt*(t+1)/2

fmax = xt/t

x = ssym("x", t+1)
x_lb =  0.0 * NP.ones(t+1)
x_ub =   xt * NP.ones(t+1)
x_guess =  NP.array(list(i*h for i in range(t+1)))

x_lb[0] = 0.0
x_ub[0] = 0.0

y = ssym("y", t+1)
y_lb = -inf * NP.ones(t+1)
y_ub =  inf * NP.ones(t+1)
y_guess = 0.0 * NP.ones(t+1)

y_lb[0] = 0.0
y_ub[0] = 0.0

z = ssym("z", t+1)
z_lb = -inf * NP.ones(t+1)
z_ub =  inf * NP.ones(t+1)
z_guess = 0.0 * NP.ones(t+1)

z_lb[0] = 1.0
z_ub[0] = 1.0

vx = ssym("vx", t+1)
vx_lb = -inf * NP.ones(t+1)
vx_ub =  inf * NP.ones(t+1)
vx_guess = 1.0 * NP.ones(t+1)

vx_lb[0] = 0.0
vx_ub[0] = 0.0
vx_lb[t] = 0.0
vx_ub[t] = 0.0

vy = ssym("vy", t+1)
vy_lb = -inf * NP.ones(t+1)
vy_ub =  inf * NP.ones(t+1)
vy_guess = 0.0 * NP.ones(t+1)

vy_lb[0] = 0.0
vy_ub[0] = 0.0
vy_lb[t] = 0.0
vy_ub[t] = 0.0

vz = ssym("vz", t+1)
vz_lb = -inf * NP.ones(t+1)
vz_ub =  inf * NP.ones(t+1)
vz_guess = 0.0 * NP.ones(t+1)

vz_lb[0] = 0.0
vz_ub[0] = 0.0
vz_lb[t] = 0.0
vz_ub[t] = 0.0

ux = ssym("ux", t)
ux_lb = -fmax * NP.ones(t)
ux_ub =  fmax * NP.ones(t)
ux_guess = 0.0 * NP.ones(t)

uy = ssym("uy", t)
uy_lb = -fmax * NP.ones(t)
uy_ub =  fmax * NP.ones(t)
uy_guess = 0.0 * NP.ones(t)

uz = ssym("uz", t)
uz_lb = -fmax * NP.ones(t)
uz_ub =  fmax * NP.ones(t)
uz_guess = 0.0 * NP.ones(t)

# All variables
v = vertcat([x,y,z,vx,vy,vz,ux,uy,uz])
v_lb = NP.concatenate([x_lb,y_lb,z_lb,vx_lb,vy_lb,vz_lb,ux_lb,uy_lb,uz_lb])
v_ub = NP.concatenate([x_ub,y_ub,z_ub,vx_ub,vy_ub,vz_ub,ux_ub,uy_ub,uz_ub])
v_guess = NP.concatenate([x_guess,y_guess,z_guess,vx_guess,vy_guess,vz_guess,ux_guess,uy_guess,uz_guess])

# Make xt, h, mass symbolic once
xt = SXMatrix(xt)
h = SXMatrix(h)
mass = SXMatrix(mass)
tol = SXMatrix(tol)

# Objective function
f = 0
for i in range(1,t+1):
  f += (i*h/w)*(x[i] - xt)**2
  
ffcn = SXFunction([v],[f])

# Constraint functions
acx = []
acx_lb = []
acx_ub = []
for i in range(1,t+1):
  acx.append(mass*(vx[i]-vx[i-1])/h - ux[i-1])
  acx_lb.append(0)
  acx_ub.append(0)
  
acy = []
acy_lb = []
acy_ub = []
for i in range(1,t+1):
  acy.append(mass*(vy[i]-vy[i-1])/h - uy[i-1])
  acy_lb.append(0)
  acy_ub.append(0)
  
acz = []
acz_lb = []
acz_ub = []
for i in range(1,t+1):
  acz.append(mass*(vz[i]-vz[i-1])/h - uz[i-1])
  acz_lb.append(0)
  acz_ub.append(0)

psx = []
psx_lb = []
psx_ub = []
for i in range(1,t+1):
  psx.append((x[i]-x[i-1])/h - vx[i])
  psx_lb.append(0)
  psx_ub.append(0)

psy = []
psy_lb = []
psy_ub = []
for i in range(1,t+1):
  psy.append((y[i]-y[i-1])/h - vy[i])
  psy_lb.append(0)
  psy_ub.append(0)

psz = []
psz_lb = []
psz_ub = []
for i in range(1,t+1):
  psz.append((z[i]-z[i-1])/h - vz[i])
  psz_lb.append(0)
  psz_ub.append(0)

sc = []
sc_lb = []
sc_ub = []
for i in range(1,t+1):
  sc.append((y[i] - sin(x[i]))**2 + (z[i] - cos(x[i]))**2 - tol**2)
  sc_lb.append(-inf)
  sc_ub.append(0)
  
g = vertcat([acx,acy,acz,psx,psy,psz,sc])
g_lb = NP.concatenate([acx_lb,acy_lb,acz_lb,psx_lb,psy_lb,psz_lb,sc_lb])
g_ub = NP.concatenate([acx_ub,acy_ub,acz_ub,psx_ub,psy_ub,psz_ub,sc_ub])

gfcn = SXFunction([v],[g])

# NLP solver
nlp_solver = IpoptSolver(ffcn,gfcn)
#nlp_solver.setOption("max_iter",10)
nlp_solver.setOption("generate_hessian",True)
nlp_solver.setOption("linear_solver","ma57")
nlp_solver.init()
nlp_solver.setInput(v_guess, NLP_X_INIT)
nlp_solver.setInput(v_lb, NLP_LBX)
nlp_solver.setInput(v_ub, NLP_UBX)
nlp_solver.setInput(g_lb, NLP_LBG)
nlp_solver.setInput(g_ub, NLP_UBG)

nlp_solver.solve()



