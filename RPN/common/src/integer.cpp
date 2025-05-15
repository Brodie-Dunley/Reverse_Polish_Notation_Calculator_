/*!	\file	integer.cpp
	\brief	Integer class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Integer class derived from Operand.

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

Version 2012.11.16
	Added Bit operators, Pow

Version 2012.11.15
	Added BinaryInteger, Binary <function>

Version 2012.11.13
	C++ 11 cleanup

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

#include <ee/integer.hpp>
#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <ee/boolean.hpp>
#include <ee/variable.hpp>
#include <ee/real.hpp>
#include <array>
#include <cmath>
using namespace std;



[[nodiscard]] Integer::string_type Integer::str() const {
	return value().str();
}
Real::value_type toRealValue(const std::shared_ptr<Operand>& operand);
Real::value_type fast_power(Real::value_type base, Real::value_type exponent);
Real::value_type simple_power(Real::value_type base, Real::value_type exponent);
Integer::value_type int_fast_power(Integer::value_type base, Integer::value_type exponent)
{
	if (exponent.is_zero())
		return 1;
	auto x = int_fast_power(base, exponent / 2);
	if (exponent % 2 == 0)
		return x * x;
	else
		return x * x * base;
}
Integer::value_type int_simple_power(Integer::value_type base, Integer::value_type exponent)
{
	Integer::value_type product = 1;
	for (Integer::value_type i = 0; i < exponent; ++i)
		product *= base;
	return product;
}
void Integer::perform_addition(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	//Handling mixed types here
	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {
			operandList.push(make_shared<Integer>(left_int->value() + right_int->value()));
		}
	}
	else
	{
		Real::value_type right_value = toRealValue(right);
		Real::value_type left_value = toRealValue(left);
		operandList.push(make_shared<Real>(left_value + right_value));
	}
	
}
void Integer::perform_subtraction(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	//Handling mixed types here
	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {
			operandList.push(make_shared<Integer>(left_int->value() - right_int->value()));
		}
	}
	else
	{
		Real::value_type right_value = toRealValue(right);
		Real::value_type left_value = toRealValue(left);
		operandList.push(make_shared<Real>(left_value - right_value));
	}
	
}

void Integer::perform_multiplication(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	//Handling mixed types here
	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {
			operandList.push(make_shared<Integer>(left_int->value() * right_int->value()));
		}
	}
	else
	{
		Real::value_type right_value = toRealValue(right);
		Real::value_type left_value = toRealValue(left);
		operandList.push(make_shared<Real>(left_value * right_value));
	}
	
}

void Integer::perform_division(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	//Handling mixed types here
	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {
			operandList.push(make_shared<Integer>(left_int->value() / right_int->value()));
		}
	}
	else
	{
		Real::value_type right_value = toRealValue(right);
		Real::value_type left_value = toRealValue(left);
		operandList.push(make_shared<Real>(left_value / right_value));
	}

}

void Integer::perform_factorial(std::stack<std::shared_ptr<Operand>>& operandList) const
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

void Integer::perform_Identity(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto result = static_cast<Integer::value_type>(arg->value());

	operandList.push(make_shared<Integer>(result));
}
void Integer::perform_Negation(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto result = static_cast<Integer::value_type>(arg->value() * -1);

	operandList.push(make_shared<Integer>(result));
}

void Integer::perform_Power(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {


			Integer::value_type base = left_int->value();
			Integer::value_type exponent = right_int->value();

			
			if (exponent <= 8)
			{
				auto result = int_simple_power(base, exponent);
				operandList.push(make_shared<Integer>(result));
			}
			else
			{
				auto result = int_fast_power(base, exponent);
				operandList.push(make_shared<Integer>(result));
			}

		}
	}
	else
	{
		Real::value_type exponent = toRealValue(right);
		Real::value_type base = toRealValue(left);
		if (exponent > 8)
		{
			Real::value_type result = fast_power(base, exponent);
			operandList.push(make_shared<Real>(result));
		}
		else
		{
			Real::value_type result = simple_power(base, exponent);
			operandList.push(make_shared<Real>(result));
		}
	}
}

void Integer::perform_Modulus(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg2 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = static_cast<Integer::value_type>(arg1->value() % arg2->value());
	auto final_r = make_shared<Integer>(result);
	operandList.push(final_r);
}
void Integer::perform_Equality(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Integer>(right)) {
			bool result = left_real->value() == right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int == right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}
void Integer::perform_Inequality(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Integer>(right)) {
			bool result = left_real->value() != right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int != right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}

void Integer::perform_Greater(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Integer>(right)) {
			bool result = left_real->value() > right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int > right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}

void Integer::perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Integer>(right)) {
			bool result = left_real->value() >= right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int >= right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}
void Integer::perform_Less(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Integer>(right)) {
			bool result = left_real->value() < right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int < right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}
void Integer::perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Integer>(right)) {
			bool result = left_real->value() <= right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int <= right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}
void Integer::perform_Floor(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = std::floor(static_cast<long double>(arg1->value()));
	auto result_f = static_cast<int>(result);
	operandList.push(make_shared<Integer>(result_f));
}
void Integer::perform_Ceil(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Integer>(operandList.top());
	operandList.pop();

	auto result = std::floor(static_cast<long double>(arg1->value()));
	auto result_f = static_cast<int>(result);
	operandList.push(make_shared<Integer>(result_f));
}
void Integer::perform_Abs(std::stack<Operand::pointer_type>& operandList) const {
	auto arg = std::dynamic_pointer_cast<Integer>(operandList.top());
	auto result = static_cast<Integer::value_type>(abs(arg->value()));
	operandList.pop();
	operandList.push(make_shared<Integer>(result));
}
void Integer::perform_Arctan(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::atan(double_y);

	operandList.push(std::make_shared<Real>(result));
}
void Integer::perform_Arcsin(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::asin(double_y);

	operandList.push(std::make_shared<Real>(result));
}
void Integer::perform_Exp(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::exp(double_y);

	operandList.push(std::make_shared<Real>(result));
}
void Integer::perform_Ln(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::log(arg1->value());
	//std::log(static_cast<long double>(arg1->value()));
	operandList.push(std::make_shared<Real>(result));


}
void Integer::perform_Lb(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::log2(arg1->value());
	//std::log2(static_cast<long double>(arg1->value()));
	operandList.push(std::make_shared<Real>(result));
}
void Integer::perform_Sqrt(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::sqrt(arg1->value());
	operandList.push(std::make_shared<Real>(result));
}
void Integer::perform_Cos(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = arg->value();
	auto result = boost::multiprecision::cos(real_arg);

	operandList.push(std::make_shared<Real>(result));
}
void Integer::perform_Arccos(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::math::acosh(double_y);

	operandList.push(std::make_shared<Real>(result));
}

void Integer::perform_Arctan2(std::stack<std::shared_ptr<Operand>>& operandList) const
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
void Integer::perform_Min(std::stack<Operand::pointer_type>& operandList) const {
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	//Handling mixed types here
	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {
			operandList.push(make_shared<Integer>(std::min(left_int->value(), right_int->value())));
		}
	}
	else
	{
		Real::value_type right_value = toRealValue(right);
		Real::value_type left_value = toRealValue(left);
		operandList.push(make_shared<Real>(boost::multiprecision::min(left_value, right_value)));
	}
	

}
void Integer::perform_Max(std::stack<Operand::pointer_type>& operandList) const {
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	//Handling mixed types here
	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {
			operandList.push(make_shared<Integer>(std::max(left_int->value(), right_int->value())));
		}
	}
	else
	{
		Real::value_type right_value = toRealValue(right);
		Real::value_type left_value = toRealValue(left);
		operandList.push(make_shared<Real>(boost::multiprecision::max(left_value,right_value)));
	}
	
}
void Integer::perform_Pow(std::stack<std::shared_ptr<Operand>>& operandList) const
{

	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_int = std::dynamic_pointer_cast<Integer>(left)) {
		if (auto right_int = std::dynamic_pointer_cast<Integer>(right)) {


			Integer::value_type base = left_int->value();
			Integer::value_type exponent = right_int->value();

			if (exponent <= 8)
			{
				auto result = int_simple_power(base, exponent);
				operandList.push(make_shared<Integer>(result));
			}
			else
			{
				auto result = int_fast_power(base, exponent);
				operandList.push(make_shared<Integer>(result));
			}

		}
	}
	else
	{
		Real::value_type exponent = toRealValue(right);
		Real::value_type base = toRealValue(left);
		if (exponent > 8)
		{
			Real::value_type result = fast_power(base, exponent);
			operandList.push(make_shared<Real>(result));
		}
		else
		{
			Real::value_type result = simple_power(base, exponent);
			operandList.push(make_shared<Real>(result));
		}
	}
}









