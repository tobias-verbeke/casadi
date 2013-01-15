/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/** All edits to this file will be lost - autogenerated by misc/autogencode.py */
#ifndef AUTOGENERATED_HPP
#define AUTOGENERATED_HPP
#include <vector>
#include <string>
#include <utility>
#include <map>
#include "casadi_exception.hpp"
namespace CasADi{
enum InputOutputScheme { SCHEME_ACADO_Input, SCHEME_ACADO_Output, SCHEME_ACADO_FCN_Input, SCHEME_ControlledDAEInput, SCHEME_ControlSimulatorInput, SCHEME_DAEInput, SCHEME_DAEOutput, SCHEME_RDAEInput, SCHEME_RDAEOutput, SCHEME_IntegratorInput, SCHEME_IntegratorOutput, SCHEME_NLPInput, SCHEME_NLPOutput, SCHEME_MayerInput, SCHEME_OCPInput, SCHEME_OCPOutput, SCHEME_QPInput, SCHEME_QPOutput, SCHEME_SDPInput, SCHEME_SDPOutput , SCHEME_unknown};
std::string getSchemeEntryName(InputOutputScheme scheme, int i);
std::string getSchemeEntryDoc(InputOutputScheme scheme, int i);
std::string getSchemeEntryEnumName(InputOutputScheme scheme, int i);
int getSchemeEntryEnum(InputOutputScheme scheme, const std::string &name);
std::string getSchemeName(InputOutputScheme scheme);
std::string getSchemeEntryNames(InputOutputScheme scheme);
/// Helper function for 'ACADO_Input'
/// Input arguments of an ACADO OCP solver
/// 
/// \copydoc scheme_ACADO_Input
template<class M>
std::vector<M> acadoIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M(),const std::string arg_s6="",M arg_m6=M(),const std::string arg_s7="",M arg_m7=M(),const std::string arg_s8="",M arg_m8=M(),const std::string arg_s9="",M arg_m9=M(),const std::string arg_s10="",M arg_m10=M(),const std::string arg_s11="",M arg_m11=M(),const std::string arg_s12="",M arg_m12=M(),const std::string arg_s13="",M arg_m13=M(),const std::string arg_s14="",M arg_m14=M(),const std::string arg_s15="",M arg_m15=M(),const std::string arg_s16="",M arg_m16=M()){
  std::vector<M> ret(17);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  if (arg_s6!="") arg.insert(make_pair(arg_s6,arg_m6));
  if (arg_s7!="") arg.insert(make_pair(arg_s7,arg_m7));
  if (arg_s8!="") arg.insert(make_pair(arg_s8,arg_m8));
  if (arg_s9!="") arg.insert(make_pair(arg_s9,arg_m9));
  if (arg_s10!="") arg.insert(make_pair(arg_s10,arg_m10));
  if (arg_s11!="") arg.insert(make_pair(arg_s11,arg_m11));
  if (arg_s12!="") arg.insert(make_pair(arg_s12,arg_m12));
  if (arg_s13!="") arg.insert(make_pair(arg_s13,arg_m13));
  if (arg_s14!="") arg.insert(make_pair(arg_s14,arg_m14));
  if (arg_s15!="") arg.insert(make_pair(arg_s15,arg_m15));
  if (arg_s16!="") arg.insert(make_pair(arg_s16,arg_m16));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_ACADO_Input,it->first);
    if (n==-1)
      casadi_error("Keyword error in ACADO_Input: '" << it->first << "' is not recognized. Available keywords are: x_guess, u_guess, p_guess, lbx, ubx, lbx0, ubx0, lbxf, ubxf, lbu, ubu, lbp, ubp, lbc, ubc, lbr, ubr");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'ACADO_Output'
/// Output arguments of an ACADO OCP solver
/// 
/// \copydoc scheme_ACADO_Output
template<class M>
std::vector<M> acadoOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M()){
  std::vector<M> ret(4);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_ACADO_Output,it->first);
    if (n==-1)
      casadi_error("Keyword error in ACADO_Output: '" << it->first << "' is not recognized. Available keywords are: x_opt, u_opt, p_opt, cost");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'ACADO_FCN_Input'
/// Input arguments of an ACADO function
/// 
/// \copydoc scheme_ACADO_FCN_Input
template<class M>
std::vector<M> acadofcnIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M()){
  std::vector<M> ret(6);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_ACADO_FCN_Input,it->first);
    if (n==-1)
      casadi_error("Keyword error in ACADO_FCN_Input: '" << it->first << "' is not recognized. Available keywords are: t, xd, xa, u, p, xdot");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'ControlledDAEInput'
/// Input arguments of an ODE/DAE function
/// 
/// \copydoc scheme_ControlledDAEInput
template<class M>
std::vector<M> controldaeIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M(),const std::string arg_s6="",M arg_m6=M(),const std::string arg_s7="",M arg_m7=M(),const std::string arg_s8="",M arg_m8=M()){
  std::vector<M> ret(9);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  if (arg_s6!="") arg.insert(make_pair(arg_s6,arg_m6));
  if (arg_s7!="") arg.insert(make_pair(arg_s7,arg_m7));
  if (arg_s8!="") arg.insert(make_pair(arg_s8,arg_m8));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_ControlledDAEInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in ControlledDAEInput: '" << it->first << "' is not recognized. Available keywords are: t, x, z, p, u, u_interp, x_major, t0, tf");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'ControlSimulatorInput'
/// Input arguments of a control simulator
/// 
/// \copydoc scheme_ControlSimulatorInput
template<class M>
std::vector<M> controlsimulatorIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M()){
  std::vector<M> ret(3);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_ControlSimulatorInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in ControlSimulatorInput: '" << it->first << "' is not recognized. Available keywords are: x0, p, u");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'DAEInput'
/// Input arguments of an ODE/DAE function
/// 
/// \copydoc scheme_DAEInput
template<class M>
std::vector<M> daeIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M()){
  std::vector<M> ret(4);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_DAEInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in DAEInput: '" << it->first << "' is not recognized. Available keywords are: x, z, p, t");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'DAEOutput'
/// Output arguments of an DAE function
/// 
/// \copydoc scheme_DAEOutput
template<class M>
std::vector<M> daeOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M()){
  std::vector<M> ret(3);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_DAEOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in DAEOutput: '" << it->first << "' is not recognized. Available keywords are: ode, alg, quad");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'RDAEInput'
/// Input arguments of an ODE/DAE backward integration function
/// 
/// \copydoc scheme_RDAEInput
template<class M>
std::vector<M> rdaeIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M(),const std::string arg_s6="",M arg_m6=M()){
  std::vector<M> ret(7);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  if (arg_s6!="") arg.insert(make_pair(arg_s6,arg_m6));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_RDAEInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in RDAEInput: '" << it->first << "' is not recognized. Available keywords are: rx, rz, rp, x, z, p, t");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'RDAEOutput'
/// Output arguments of an ODE/DAE backward integration function
/// 
/// \copydoc scheme_RDAEOutput
template<class M>
std::vector<M> rdaeOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M()){
  std::vector<M> ret(3);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_RDAEOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in RDAEOutput: '" << it->first << "' is not recognized. Available keywords are: ode, alg, quad");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'IntegratorInput'
/// Input arguments of an integrator
/// 
/// \copydoc scheme_IntegratorInput
template<class M>
std::vector<M> integratorIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M()){
  std::vector<M> ret(4);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_IntegratorInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in IntegratorInput: '" << it->first << "' is not recognized. Available keywords are: x0, p, rx0, rp");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'IntegratorOutput'
/// Output arguments of an integrator
/// 
/// \copydoc scheme_IntegratorOutput
template<class M>
std::vector<M> integratorOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M()){
  std::vector<M> ret(4);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_IntegratorOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in IntegratorOutput: '" << it->first << "' is not recognized. Available keywords are: xf, qf, rxf, rqf");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'NLPInput'
/// Input arguments of an NLP Solver
/// 
/// \copydoc scheme_NLPInput
template<class M>
std::vector<M> nlpsolverIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M(),const std::string arg_s6="",M arg_m6=M()){
  std::vector<M> ret(7);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  if (arg_s6!="") arg.insert(make_pair(arg_s6,arg_m6));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_NLPInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in NLPInput: '" << it->first << "' is not recognized. Available keywords are: x_init, lbx, ubx, lbg, ubg, lambda_init, p");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'NLPOutput'
/// Output arguments of an NLP Solver
/// 
/// \copydoc scheme_NLPOutput
template<class M>
std::vector<M> nlpsolverOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M()){
  std::vector<M> ret(5);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_NLPOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in NLPOutput: '" << it->first << "' is not recognized. Available keywords are: x_opt, cost, lambda_g, lambda_x, g");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'MayerInput'
/// Input arguments of a Mayer Term \n
/// nx: Number of states: from ffcn.input(INTEGRATOR_X0).size() \n
/// np: Number of parameters: from option number_of_parameters\n
/// 
/// \copydoc scheme_MayerInput
template<class M>
std::vector<M> mayerIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M()){
  std::vector<M> ret(2);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_MayerInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in MayerInput: '" << it->first << "' is not recognized. Available keywords are: x, p");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'OCPInput'
/// Input arguments of an OCP Solver \n
/// ns: Number of shooting nodes: from option number_of_grid_points\n
/// nx: Number of states: from ffcn.input(INTEGRATOR_X0).size() \n
/// nc: Number of constants duting intergation: ffcn.input(INTEGRATOR_P).size()
/// nu: Number of controls: from nc - np \n
/// np: Number of parameters: from option number_of_parameters\n
/// nh: Number of point constraints: from cfcn.input(0).size()
/// 
/// \copydoc scheme_OCPInput
template<class M>
std::vector<M> ocpIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M(),const std::string arg_s6="",M arg_m6=M(),const std::string arg_s7="",M arg_m7=M(),const std::string arg_s8="",M arg_m8=M(),const std::string arg_s9="",M arg_m9=M(),const std::string arg_s10="",M arg_m10=M(),const std::string arg_s11="",M arg_m11=M(),const std::string arg_s12="",M arg_m12=M()){
  std::vector<M> ret(13);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  if (arg_s6!="") arg.insert(make_pair(arg_s6,arg_m6));
  if (arg_s7!="") arg.insert(make_pair(arg_s7,arg_m7));
  if (arg_s8!="") arg.insert(make_pair(arg_s8,arg_m8));
  if (arg_s9!="") arg.insert(make_pair(arg_s9,arg_m9));
  if (arg_s10!="") arg.insert(make_pair(arg_s10,arg_m10));
  if (arg_s11!="") arg.insert(make_pair(arg_s11,arg_m11));
  if (arg_s12!="") arg.insert(make_pair(arg_s12,arg_m12));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_OCPInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in OCPInput: '" << it->first << "' is not recognized. Available keywords are: lbx, ubx, x_init, lbu, ubu, u_init, lbp, ubp, p_init, lbh, ubh, lbg, ubg");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'OCPOutput'
/// Output arguments of an OCP Solver
/// 
/// \copydoc scheme_OCPOutput
template<class M>
std::vector<M> ocpOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M()){
  std::vector<M> ret(4);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_OCPOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in OCPOutput: '" << it->first << "' is not recognized. Available keywords are: x_opt, u_opt, p_opt, cost");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'QPInput'
/// Input arguments of a QP problem
/// 
/// \copydoc scheme_QPInput
template<class M>
std::vector<M> qpIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M(),const std::string arg_s5="",M arg_m5=M(),const std::string arg_s6="",M arg_m6=M(),const std::string arg_s7="",M arg_m7=M(),const std::string arg_s8="",M arg_m8=M()){
  std::vector<M> ret(9);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  if (arg_s5!="") arg.insert(make_pair(arg_s5,arg_m5));
  if (arg_s6!="") arg.insert(make_pair(arg_s6,arg_m6));
  if (arg_s7!="") arg.insert(make_pair(arg_s7,arg_m7));
  if (arg_s8!="") arg.insert(make_pair(arg_s8,arg_m8));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_QPInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in QPInput: '" << it->first << "' is not recognized. Available keywords are: h, g, a, lba, uba, lbx, ubx, x_init, lambda_init");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'QPOutput'
/// Output arguments of an QP Solver
/// 
/// \copydoc scheme_QPOutput
template<class M>
std::vector<M> qpOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M()){
  std::vector<M> ret(4);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_QPOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in QPOutput: '" << it->first << "' is not recognized. Available keywords are: primal, cost, lambda_a, lambda_x");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'SDPInput'
/// Input arguments of a SDP problem
/// 
/// \copydoc scheme_SDPInput
template<class M>
std::vector<M> sdpIn(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M()){
  std::vector<M> ret(3);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_SDPInput,it->first);
    if (n==-1)
      casadi_error("Keyword error in SDPInput: '" << it->first << "' is not recognized. Available keywords are: a, b, c");
    ret[n] = it->second;
  }
  return ret;
}
/// Helper function for 'SDPOutput'
/// Output arguments of an SDP Solver
/// 
/// \copydoc scheme_SDPOutput
template<class M>
std::vector<M> sdpOut(const std::string arg_s0="",M arg_m0=M(),const std::string arg_s1="",M arg_m1=M(),const std::string arg_s2="",M arg_m2=M(),const std::string arg_s3="",M arg_m3=M(),const std::string arg_s4="",M arg_m4=M()){
  std::vector<M> ret(5);
  std::map<std::string,M> arg;
  if (arg_s0!="") arg.insert(make_pair(arg_s0,arg_m0));
  if (arg_s1!="") arg.insert(make_pair(arg_s1,arg_m1));
  if (arg_s2!="") arg.insert(make_pair(arg_s2,arg_m2));
  if (arg_s3!="") arg.insert(make_pair(arg_s3,arg_m3));
  if (arg_s4!="") arg.insert(make_pair(arg_s4,arg_m4));
  typedef typename std::map<std::string,M>::const_iterator it_type;
  for(it_type it = arg.begin(); it != arg.end(); it++) {
    int n = getSchemeEntryEnum(SCHEME_SDPOutput,it->first);
    if (n==-1)
      casadi_error("Keyword error in SDPOutput: '" << it->first << "' is not recognized. Available keywords are: primal, p, dual, primal_cost, dual_cost");
    ret[n] = it->second;
  }
  return ret;
}
}
#endif //AUTOGENERATED_HPP