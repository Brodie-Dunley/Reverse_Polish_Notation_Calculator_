#pragma once
/*!	\file	integer.hpp
	\brief	Integer class declaration.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Integer class derived from Operand.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2014.10.29
	C++ 11 refactor.
	Converted Integer::value_type to boost::multiprecision::cpp_int
	Removed BinaryInteger

Version 2012.11.15
	Added BinaryInteger.

Version 2012.11.13
	C++ 11 cleanup.

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.
	Switched __int64 to long long.

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
#include <boost/multiprecision/cpp_int.hpp>
#include <ee/real.hpp>



/*! Integer token. */
class Integer : public Operand {
public:
	using value_type = boost::multiprecision::cpp_int;
	DEF_POINTER_TYPE(Integer)
private:
	value_type	value_;
public:
	Integer( value_type value = 0 )
		: value_( value ) { }
	

	[[nodiscard]]	value_type	value() const { return value_; }
	[[nodiscard]]	string_type	str() const override;

	bool operator == (const Integer& rhs) const
	{
		return this->value_ == rhs.value_;
	}
	bool operator ==(const value_type& rhs)const
	{
		return this->value_ == rhs;
	}
	void perform_addition(std::stack<std::shared_ptr<Operand>>& operandList) const;
	void perform_subtraction(std::stack<std::shared_ptr<Operand>>& operandList) const;
	void perform_multiplication(std::stack<std::shared_ptr<Operand>>& operandList) const;
	void perform_division(std::stack<Operand::pointer_type>& operandList) const;
	void perform_factorial(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Identity(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Negation(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Power(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Modulus(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Arccos(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Arcsin(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Arctan(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Lb(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Ln(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Exp(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Arctan2(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Sqrt(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Cos(std::stack<Operand::pointer_type>& operandList) const;


	void perform_Abs(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Min(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Max(std::stack<Operand::pointer_type>& operandList) const;
	
	void perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const;
	void perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Equality(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Inequality(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Less(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Greater(std::stack<Operand::pointer_type>& operandList) const;

	void perform_Ceil(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Floor(std::stack<Operand::pointer_type>& operandList) const;
	void perform_Pow(std::stack<Operand::pointer_type>& operandList) const;

	//void perform_Result(std::stack<std::shared_ptr<Operand>>& operandList, std::vector<std::shared_ptr<Token>> resultHistory) const;


};
