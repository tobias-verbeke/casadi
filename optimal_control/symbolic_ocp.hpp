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

#ifndef SYMBOLIC_OCP_HPP
#define SYMBOLIC_OCP_HPP

#include "variable.hpp"

namespace CasADi{
  
  // Forward declarations
  class XMLNode;
  
  
/** \brief A flat OCP representation coupled to an XML file

 <H3>Variables:  </H3>
  \verbatim
   t :     time
   x :     differential and algebraic states defined by a fully-implicit DAE
   xd:     differential states defined by an explicit ODE
   xa:     algebraic states defined by an algebraic equation
   q :     quadrature states
   y :     dependent variables
   p :     independent parameters
   u :     control signals
  \endverbatim 
  
  <H3>Equations:  </H3>
  \verbatim
  fully implicit DAE:       0 = dae(t,x,\dot{x},xd,xa,u,p)
  explicit ODE:      \dot{xd} = ode(t,x,xd,xa,u,p)
  quadratures:        \dot{q} = quad(t,x,xd,xa,u,p)
  algebraic equations:      0 = alg(t,x,xd,xa,u,p)
  dependent equations:      y = dep(t,x,xd,xa,u,p)
  initial equations:        0 = initial(t,x,\dot{x},xd,xa,u,p)
  \endverbatim 

  <H3>Objective function terms:  </H3>
  \verbatim
  Mayer terms:          \sum{mterm_k}
  Lagrange terms:       \sum{\integral{mterm}}
  \endverbatim

  Note that when parsed, all dynamic states, differential and algebraic, end up in the category "x" 
  and all dynamic equations end up in the implicit category "dae". At a later state, the DAE can be
  reformulated, for example in semi-explicit form, possibly in addition to a set of quadrature states.
 
  Also note that division of the states into three categories for states defined by a DAE, states
  defined by an ODE and states defined by an algebraic equation. The category "xd" does thus _not_
  include differential states that are implicitly defined by the DAE.

  The functions for reformulation is are provided as member functions to this class or as independent
  functions located in the header file "ocp_tools.hpp".

  <H3>Usage skeleton:</H3>
  
  1. Call default constructor 
  > SymbolicOCP ocp;
  
  2. Parse an FMI conformant XML file <BR>
  > ocp.parseFMI(xml_file_name)
  
  3. Modify/add variables, equations, optimization <BR>
  > ...
  
  When the optimal control problem is in a suitable form, it is possible to either generate functions
  for numeric/symbolic evaluation or exporting the OCP formulation into a new FMI conformant XML file.
  The latter functionality is not yet available.

  \date 2012
  \author Joel Andersson
*/
class SymbolicOCP : public PrintableObject{
  public:

    /// Default constructor
    SymbolicOCP();
    
    /** @name Variables
    *  Public data members
    */
    //@{
    /// Time
    SXMatrix t;
    
    /// Differential and algebraic states defined by a fully-implicit DAE (length == dae().size())
    std::vector<Variable> x;
    
    /// Differential states defined by an explicit ODE (length == ode().size())
    std::vector<Variable> xd;
    
    /// Algebraic states defined by an algebraic equation (length == alg().size())
    std::vector<Variable> xa;
    
    /// Quadrature states (length == quad().size())
    std::vector<Variable> xq;
    
    /// Dependent variables (length == dep().size())
    std::vector<Variable> y;
    
    /// Independent parameters
    std::vector<Variable> p;
    
    /// Control signals
    std::vector<Variable> u;

    //@}
    
    /** @name Equations
    *  Get all equations of a particular type 
    */
    //@{
      
    /// Fully implicit DAE (length == x().size())
    SXMatrix dae;
    
    /// Explicit ODE  (length == xd().size())
    SXMatrix ode;
    
    /// Algebraic equations (length == xa().size())
    SXMatrix alg;
    
    /// Quadrature states (length == q().size())
    SXMatrix quad;
    
    /// Dependent equations (length == y().size())
    SXMatrix dep;
    
    /// Initial equations (remove?)
    SXMatrix initial;
    //@}
    
    /** @name Time points
    */
    //@{

    /// Interval start time
    double t0;
    
    /// Interval final time
    double tf;
    
    /// Interval start time is free
    bool t0_free;
    
    /// Interval final time is free
    bool tf_free;
    //@}

    /** @name Objective function terms
    *  Terms in the objective function.
    */
    //@{
      
    /// Mayer terms in the objective (point terms)
    SXMatrix mterm;
    
    /// Lagrange terms in the objective (integral terms)
    SXMatrix lterm;
    //@}

    /** @name Constraints of the optimal control problem
    */
    //@{

    /// Path constraint functions
    SXMatrix path;
    
    /// Path constraint functions upper bounds
    DMatrix path_min;

    /// Path constraint functions upper bounds
    DMatrix path_max;
    //@}

    /// Parse from XML to C++ format
    void parseFMI(const std::string& filename, const Dictionary& options = Dictionary());

    /// Add a variable
    void addVariable(const std::string& name, const Variable& var);
    
    /// Access a variable by name
    Variable& variable(const std::string& name);

    /// Make a differential state algebraic by replacing its time derivative by 0
    void makeAlgebraic(const Variable& v);

    /// Make a differential state algebraic by replacing its time derivative by 0
    void makeAlgebraic(const std::string& name);
    
    /// All states, differential and algebraic (includes x, xd and xa)
    std::vector<Variable> x_all() const;
    
    /** @name Manipulation
    *  Reformulate the dynamic optimization problem.
    */
    //@{
    /// Eliminate interdependencies in the dependent equations
    void eliminateInterdependencies();
    
    /// Eliminate dependent equations, by default sparing the dependent variables with upper or lower bounds
    void eliminateDependent(bool eliminate_dependents_with_bounds=true);

    /// Eliminate Lagrange terms from the objective function and make them quadrature states
    void eliminateLagrangeTerms();
    
    /// Eliminate quadrature states and turn them into ODE states
    void eliminateQuadratureStates();
    
    /// Sort the DAE equations and variables
    void sortDAE();

    /// Transform the fully implicit DAE to a explicit or semi-explicit form
    void makeExplicit();

    /** \brief Get the ODE/DAE input arguments
    * Returns a vector of inputs using the following scheme:
    * @copydoc scheme_DAEInput 
    */
    std::vector<SXMatrix> daeArg() const;
    
    /// Substitute the dependents from a set of expressions
    std::vector<SXMatrix> substituteDependents(const std::vector<SXMatrix>& x) const;
    
    /// Generate a MUSCOD-II compatible DAT file
    void generateMuscodDatFile(const std::string& filename, const Dictionary& mc2_ops=Dictionary()) const;
    
    //@}
    
    /// Get the qualified name
    static std::string qualifiedName(const XMLNode& nn);
    
    /// Find of variable by name
    std::map<std::string,Variable> varmap_;

    /// Read an equation
    SX readExpr(const XMLNode& odenode);

    /// Read a variable
    Variable& readVariable(const XMLNode& node);

    /// Sort variables according to type
    void sortType();
    
    /// Scale the variables
    void scaleVariables();
    
    /// Scale the implicit equations
    void scaleEquations();
    
    #ifndef SWIG
    ///  Print representation
    virtual void repr(std::ostream &stream=std::cout) const;

    /// Print description 
    virtual void print(std::ostream &stream=std::cout) const;
    #endif // SWIG

};

} // namespace CasADi

#endif //SYMBOLIC_OCP_HPP