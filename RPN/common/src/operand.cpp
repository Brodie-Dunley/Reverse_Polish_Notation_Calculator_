/*!	\file	operand.cpp
	\brief	Operand class and utilities implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Operand class derived from Token and the
supporting utilities.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2017.12.12
	Added an exception to dereference when there is no value stored in the variable.

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.14
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
#include <ee/expression_evaluator.hpp>
#include <ee/boolean.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>

#include <deque>

void Operand::perform_addition(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = static_cast<Integer::value_type>(arg1->value() + arg2->value());
	auto final_r = make_shared<Integer>(result);
	operandList.push(final_r);
}
void Operand::perform_subtraction(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = static_cast<Integer::value_type>(arg1->value() - arg2->value());
	auto final_r = make_shared<Integer>(result);
	operandList.push(final_r);
}

void Operand::perform_multiplication(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = static_cast<Integer::value_type>(arg1->value() * arg2->value());
	auto final_r = make_shared<Integer>(result);
	operandList.push(final_r);
}

void Operand::perform_division(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = static_cast<Integer::value_type>(arg1->value() / arg2->value());
	auto final_r = make_shared<Integer>(result);
	operandList.push(final_r);
}

void Operand::perform_factorial(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	if (arg < 0)
		throw std::runtime_error("Factorial is undefined for negative integers");

	Integer::value_type factorialValue = 1;
	for (int i = 1; i <= arg->value(); ++i)
		factorialValue *= i;

	operandList.push(make_shared<Integer>(factorialValue));

}

void Operand::perform_Identity(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto result = static_cast<Integer::value_type>(arg->value());
	
	operandList.push(make_shared<Integer>(result));
}
void Operand::perform_Negation(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto var = std::dynamic_pointer_cast<Variable>(arg);
	if (var == nullptr) {
			throw std::runtime_error("Error: variable not initialized");
	}

	if (!arg)
		throw std::runtime_error("Not able to Negate this");
	auto result = static_cast<Integer::value_type>(arg->value() * -1);
	
	operandList.push(make_shared<Integer>(result));
}

void Operand::perform_Power(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	Integer::value_type result = 1;
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	Integer::value_type base = arg1->value();
	Integer::value_type exponent = arg2->value();
	
	while (exponent > 0) {
		if (exponent % 2 == 1) {
			result *= base;
		}
		base *= base;
		exponent /= 2;
	}
	operandList.push(make_shared<Integer>(result));
}

void Operand::perform_Modulus(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = static_cast<Integer::value_type>(arg1->value() % arg2->value());
	auto final_r = make_shared<Integer>(result);
	operandList.push(final_r);
}

void Operand::perform_Abs(std::stack<Operand::pointer_type>& operandList) const {
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	auto result = static_cast<Integer::value_type>(abs(arg->value()));
	operandList.pop();
	operandList.push(make_shared<Integer>(result));
}
void Operand::perform_Min(std::stack<Operand::pointer_type>& operandList) const {
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = std::min(arg1->value(), arg2->value());
	
	operandList.push(make_shared<Integer>(result));

}
void Operand::perform_Max(std::stack<Operand::pointer_type>& operandList) const {
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = std::max(arg1->value(), arg2->value());

	operandList.push(make_shared<Integer>(result));
}

void Operand::perform_Not(std::stack<Operand::pointer_type>& operandList) const {

	auto var_arg = std::dynamic_pointer_cast<Variable>(operandList.top());
	operandList.pop();

	bool result = !var_arg->value();
	
	operandList.push(std::make_shared<Boolean>(result));
	
}
void Operand::perform_And(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto result = arg1->value() && arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}
void Operand::perform_Nand(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() && arg2->value();

	bool nandResult = !result;

	auto result_f = static_cast<Integer::value_type>(nandResult ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}
void Operand::perform_Nor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() || arg2->value();

	bool nandResult = !result;

	auto result_f = static_cast<Integer::value_type>(nandResult ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}
void Operand::perform_Or(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() || arg2->value();

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}

void Operand::perform_Xnor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = (arg1->value() != 0) ^ (arg2->value() != 0);

	auto xnorResult = !result;

	auto result_f = static_cast<Integer::value_type>(xnorResult ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}
void Operand::perform_Xor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = (arg1->value() != 0) ^ (arg2->value() != 0);

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}

void Operand::perform_Equality(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() == arg2->value() ;

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}

void Operand::perform_Inequality(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() != arg2->value();

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}

void Operand::perform_Greater(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() > arg2->value();

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}

void Operand::perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() >= arg2->value();

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}
void Operand::perform_Less(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() < arg2->value();

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}
void Operand::perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = arg1->value() <= arg2->value();

	auto result_f = static_cast<Integer::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Integer>(result_f));
}
void Operand::perform_Sin(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = static_cast<double>(arg->value());
	auto result = static_cast<Real::value_type>(std::sin(real_arg));

	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Tan(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = static_cast<double>(arg->value());
	auto result = static_cast<Real::value_type>(std::tan(real_arg));

	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Cos(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = static_cast<double>(arg->value());
	auto result = static_cast<Real::value_type>(std::cos(real_arg));

	operandList.push(std::make_shared<Real>(result));
}

void Operand::perform_Arctan2(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto x = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto double_y = static_cast<double>(y->value());
	auto double_x = static_cast<double>(x->value());
	auto result = static_cast<Real::value_type>(std::atan2(double_y, double_x));

	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Floor(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = std::floor(static_cast<long double>(arg1->value()));
	auto result_f = static_cast<int>(result);
	operandList.push(std::make_shared<Integer>(result_f));
}
void Operand::perform_Ceil(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = std::floor(static_cast<long double>(arg1->value()));
	auto result_f = static_cast<int>(result);
	operandList.push(std::make_shared<Integer>(result_f));
}
void Operand::perform_Arctan(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::atan(double_y);
	
	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Arcsin(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::asin(double_y);
	
	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Exp(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::exp(double_y);

	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Ln(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::log(arg1->value());
	
	operandList.push(std::make_shared<Real>(result));


}
void Operand::perform_Lb(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::log2(arg1->value());
	//std::log2(static_cast<long double>(arg1->value()));
	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Sqrt(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::sqrt(arg1->value());
	operandList.push(std::make_shared<Real>(result));
}
void Operand::perform_Arccos(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::math::acosh(double_y);

	operandList.push(std::make_shared<Real>(result));
}
