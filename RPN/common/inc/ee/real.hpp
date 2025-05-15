#pragma once
/*!	\file	real.hpp
	\brief	Real classes declarations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Real classes derived from Operand.  Includes
the subclasses Pi and E.


=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.26
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2014.10.29
	C++ 11 refactor.
	Switched value_type to boost::multiprecision::cpp_dec_float_100

Version 2012.11.13
	C++ 11 cleanup

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

#include <ee/operand.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>



/*! Real number token. */
class Real : public Operand {
public:
	DEF_POINTER_TYPE(Real)
	using value_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1000, int32_t, void>>;
private:
	value_type	value_;
public:
	Real(value_type value = value_type(0)) : value_(value) { }
	

	[[nodiscard]] value_type	value() const { return value_; };
	[[nodiscard]] string_type	str() const override;
	void perform_addition(std::stack<Operand::pointer_type>& operandList) const ;
	
	void perform_subtraction(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_multiplication(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_division(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_factorial(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Identity(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Negation(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Power(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Modulus(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Min(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Max(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Abs(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_And(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Arccos(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Arcsin(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Arctan(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Arctan2(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Ceil(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Cos(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_E(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Exp(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_False(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Floor(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Lb(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Ln(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Log(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Nand(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Nor(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Not(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Or(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Pi(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Pow(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Result(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Sin(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Sqrt(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Tan(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_True(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Xnor(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Xor(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Variable(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Equality(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Inequality(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Less(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Greater(std::stack<Operand::pointer_type>& operandList) const ;
	void perform_Assignment(std::stack<Operand::pointer_type>& operandList) const ;
	//void perform_Result(std::stack<std::shared_ptr<Operand>>& operandList, std::vector<std::shared_ptr<Token>> resultHistory) const;
	
};



/*! Pi constant token. */
class Pi : public Real {
public:
	Pi() : Real(boost::math::constants::pi<value_type>()) { }
};


/*! Euler constant token. */
class E : public Real {
public:
	E() : Real(boost::math::constants::e<value_type>()) { }
};

extern bool isReal(const Token::pointer_type& token);
//Real::value_type simple_power(value_type base, value_type exponent);
//Real::value_type fast_power(value_type base, value_type exponent);