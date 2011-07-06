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

#include "binary_op.hpp"
#include "mx_tools.hpp"
#include <vector>
#include <sstream>
#include "../matrix/matrix_tools.hpp"
#include "../sx/sx_tools.hpp"

using namespace std;

namespace CasADi{

BinaryOp::BinaryOp(Operation op, MX x, MX y) : op_(op){
  if(x.numel()==1){
    // Put densifying node in between if necessary
    if(!casadi_math<double>::fx0_is_zero[op_]){
      makeDense(y); // REMOVE
    }
    
    if (x.size()==0) {
      setDependencies(0,y);
    } else {
      setDependencies(x,y);
    }
    setSparsity(y.sparsity());
    mapping_.resize(y.size(), 1 | 2 | 8);
    if(!mapping_.empty()) mapping_.back() = 1 | 2;
    
  } else if(y.numel()==1){
    // Put densifying node in between if necessary
    if(!casadi_math<double>::f0x_is_zero[op_]){
      makeDense(x); // REMOVE
    }
    
    if (y.size()==0) {
      setDependencies(x,0);
    } else {
      setDependencies(x,y);
    }
    setSparsity(x.sparsity());
    mapping_.resize(x.size(), 1 | 2 | 4);
    if(!mapping_.empty()) mapping_.back() = 1 | 2;
  } else { 
    // Put densifying nodes in between if necessary
    if(!casadi_math<double>::f00_is_zero[op_] && !(x.dense() || y.dense())){
      if(x.size()>y.size()) // enough to make one of them dense
        makeDense(x); // REMOVE
      else
        makeDense(y); // REMOVE
    }
    
    setDependencies(x,y);
    
    // Check if the sparsity patterns are the same
    bool same_sparsity_ = x.sparsity() == y.sparsity();
    
    // Get the sparsity pattern
    if(same_sparsity_){
      setSparsity(x->sparsity());
      mapping_.resize(x.size(), 1 | 2 | 4 | 8);
      if(!mapping_.empty()) mapping_.back() = 1 | 2;
    } else {
      CRSSparsity sp = x->sparsity().patternUnion(y->sparsity(),mapping_);
      setSparsity(sp);
      for(int el=0; el<mapping_.size(); ++el){
        if(mapping_[el] & 1) mapping_[el] |= 4;
        if(mapping_[el] & 2) mapping_[el] |= 8;
      }
      for(int el=mapping_.size()-1; el>=0; --el){
        if(mapping_[el] & 1){
          mapping_[el] &= ~4;
          break;
        }
      }
      for(int el=mapping_.size()-1; el>=0; --el){
        if(mapping_[el] & 2){
          mapping_[el] &= ~8;
          break;
        }
      }
    }
  }
}

MX BinaryOp::adFwd(const std::vector<MX>& jx){
  MX f = MX::create(this);
  MX pd[2];
  casadi_math<MX>::der[op_](dep(0),dep(1),f,pd);
  return pd[0]*jx[0] + pd[1]*jx[1];
}

void BinaryOp::evaluateSX(const std::vector<SXMatrix*> &input, SXMatrix& output){
  Matrix<SX>::binary_no_alloc(casadi_math<SX>::funE[op_],*input[0],*input[1],output,mapping_);
}

void BinaryOp::print(std::ostream &stream, const std::vector<std::string>& args) const{
  casadi_math<double>::print[op_](stream,args.at(0),args.at(1));
}

void BinaryOp::evaluate(const std::vector<DMatrix*>& input, DMatrix& output, const vvDMatrixP& fwdSeed, std::vector<DMatrix*>& fwdSens, const std::vector<DMatrix*>& adjSeed, vvDMatrixP& adjSens, int nfwd, int nadj){
  if(nfwd==0 && nadj==0){
    DMatrix::binary_no_alloc(casadi_math<double>::funE[op_],*input[0],*input[1],output,mapping_);
  } else {
    vector<double>& output0 = output.data();
    const vector<double> &input0 = input[0]->data();
    const vector<double> &input1 = input[1]->data();

    // Argument values
    double a[2][2] = {{0,0},{0,0}};
    if(!input0.empty()) a[0][1] = input0.front();
    if(!input1.empty()) a[1][1] = input1.front();

    // Nonzero counters
    int el0=0, el1=0;

    // Partial derivatives
      double pd[2][2] = {{0,0},{0,0}};
    
    // With sensitivities
    for(int i=0; i<mapping_.size(); ++i){
      // Check which elements are nonzero
      unsigned char m = mapping_[i];
      bool nz0 = m & 1;
      bool nz1 = m & 2;
      
      // Evaluate and get partial derivatives
      casadi_math<double>::fun[op_](a[0][nz0], a[1][nz1],output0[i]);
      casadi_math<double>::der[op_](a[0][nz0], a[1][nz1],output0[i],pd[1]);
      
      // Propagate forward seeds
      for(int d=0; d<nfwd; ++d){
        double s = 0;
        s += pd[nz0][0]*fwdSeed[0][d]->data()[el0];
        s += pd[nz1][1]*fwdSeed[1][d]->data()[el1];
        fwdSens[d]->data()[i] = s;
      }
      
      // Propagate adjoint seeds
      for(int d=0; d<nadj; ++d){
        double s = adjSeed[d]->data()[i];
        if(nz0) adjSens[0][d]->data()[el0] += s*pd[nz0][0];
        if(nz1) adjSens[1][d]->data()[el1] += s*pd[nz1][1];
      }
      
      // Go to next nonzero (and copy already now the next input to cache)
      if(m & 4) a[0][1] = input0[++el0];
      if(m & 8) a[1][1] = input1[++el1];
    }
  }
}

BinaryOp* BinaryOp::clone() const{
  return new BinaryOp(*this);
}

} // namespace CasADi
