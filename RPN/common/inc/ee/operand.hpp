#pragma once
/*!	\file	operand.hpp
	\brief	Operand class and utilities declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Operand class derived from Token and the 
supporting utilities.

	class Operand
	class NoCast
	DECL_OPERAND_PERFORM()
	DEF_OPERAND_PERFORM()
	make_operand()
	get_value()
	OperandList
	dereference()
	make_same()
	up_cast()

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.12.10
	make_operand changed to use a parameter pack

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ cleanup.

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

Version 2009.11.25
	Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <ee/token.hpp>
#include <cassert>
#include <deque>
#include <stack>

/*! Operand token base class. */
class Operand : public Token {
public:
	DEF_POINTER_TYPE(Operand)
	using operand_list_type = std::deque<Operand::pointer_type>;

	//Arithmetic Operations
	virtual void perform_addition(std::stack<std::shared_ptr<Operand>>& operandList) const;
	virtual void perform_subtraction(std::stack<std::shared_ptr<Operand>>& operandList) const;
	virtual void perform_multiplication(std::stack<std::shared_ptr<Operand>>& operandList) const;
	virtual void perform_division(std::stack<Operand::pointer_type>& operandList) const;
	void perform_factorial(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Identity(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Negation(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Power(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Modulus(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Sin(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Cos(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Tan(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Arctan2(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Arccos(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Arcsin(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Arctan(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Lb(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Ln(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Sqrt(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Exp(std::stack<Operand::pointer_type>& operandList) const;
	
	virtual void perform_Abs(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Min(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Max(std::stack<Operand::pointer_type>& operandList) const;

	//Logical operators
	virtual void perform_Not(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_And(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Nand(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Nor(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Or(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Xnor(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Xor(std::stack<Operand::pointer_type>& operandList) const;



	//Comparison for equality operators
	virtual void perform_Equality(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Inequality(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Greater(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Less(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const;

	virtual void perform_Floor(std::stack<Operand::pointer_type>& operandList) const;
	virtual void perform_Ceil(std::stack<Operand::pointer_type>& operandList) const;
	/*virtual void perform_Result(std::stack<std::shared_ptr<Operand>>& operandList, std::vector<std::shared_ptr<Token>>)const;*/
	
};


/*! Make a new smart-pointer managed Token object with constructor parameter. */
template <typename T, class... Args> inline Operand::pointer_type [[nodiscard]] make_operand(Args ... params) {
	return Operand::pointer_type(new T(params...));
}


/*! Gets the value from an operand. */
template <typename OPERAND_TYPE>
typename OPERAND_TYPE::value_type [[nodiscard]] value_of(Token::pointer_type const& operand) {
	assert(is<OPERAND_TYPE>(operand));
	return dynamic_cast<OPERAND_TYPE*>(operand.get())->value();

	
}


/*!	Type for a list of operands. */
using OperandList = Operand::operand_list_type;

extern const OperandList oList;






