/*!	\file	real.hpp
	\brief	Real classes implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Real classes derived from Operand.  Includes
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

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/special_functions/round.hpp>
#include <ee/real.hpp>
#include <ee/boolean.hpp>
#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <ee/variable.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <ee/integer.hpp>
#include <sstream>
using namespace std;
using value_type = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1000, int32_t, void>>;

[[nodiscard]] Real::string_type Real::str() const {
	ostringstream oss;
	oss << /*"Real: " << */fixed << setprecision(numeric_limits<value_type>::digits10) << value_;
	return oss.str();
}

value_type toRealValue(const std::shared_ptr<Operand>& operand) {
	if (auto real = std::dynamic_pointer_cast<Real>(operand)) {
		return real->value();
	}
	if (auto integer = std::dynamic_pointer_cast<Integer>(operand)) {
		return static_cast<Real::value_type>(integer->value());
	}
	throw std::runtime_error("Unsupported operand type");
}

bool isReal(const Token::pointer_type& token)
{
	static const std::vector<std::string> functionList{
		"<Pi>" ,"<E>"
	};

	auto it = std::find(functionList.begin(), functionList.end(), token->str());
	if (it != functionList.end())
		return true;

	return false;
}
void Real::perform_Identity(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto result = static_cast<Real::value_type>(arg->value());

	operandList.push(make_shared<Real>(result));
}
void Real::perform_Negation(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto result = static_cast<Real::value_type>(arg->value() * -1);

	operandList.push(make_shared<Real>(result));
}
void Real::perform_Sin(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = arg->value();
	auto result = boost::multiprecision::sin(real_arg);
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Tan(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = arg->value();
	auto result = boost::multiprecision::tan(real_arg);
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Cos(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto real_arg = arg->value();
	auto result = boost::multiprecision::cos(real_arg);
	operandList.push(make_shared<Real>(result));
}

void Real::perform_Arctan2(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	auto x = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();
	auto double_x = x->value();

	auto result = boost::multiprecision::atan2(double_x, double_y);
		
	operandList.push(make_shared<Real>(result));
}
void Real::perform_addition(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();
	
	Real::value_type right_value = toRealValue(right);
	Real::value_type left_value = toRealValue(left);
	Real::value_type result = left_value + right_value;

	operandList.push(std::make_shared<Real>(result));

	
}
void Real::perform_subtraction(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	Real::value_type right_value = toRealValue(right);
	Real::value_type left_value = toRealValue(left);
	Real::value_type result = left_value - right_value;

	operandList.push(std::make_shared<Real>(result));
}

void Real::perform_multiplication(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	Real::value_type right_value = toRealValue(right);
	Real::value_type left_value = toRealValue(left);
	Real::value_type result = left_value * right_value;
	
	operandList.push(std::make_shared<Real>(result));
}

void Real::perform_division(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	if (right == 0)
		throw std::runtime_error("Cannot Divide by 0");
	auto left = operandList.top();
	operandList.pop();

	Real::value_type right_value = toRealValue(right);
	Real::value_type left_value = toRealValue(left);
	Real::value_type result = left_value / right_value;
	operandList.push(std::make_shared<Real>(result));
}
void Real::perform_Not(std::stack<Operand::pointer_type>& operandList) const {

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = !arg1->value();

	auto result_f = static_cast<Real::value_type>(result);
	operandList.push(make_shared<Real>(result_f));

}
void Real::perform_And(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = arg1->value() && arg2->value();

	auto result_f = static_cast<Real::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Real>(result_f));
}
void Real::perform_Nand(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = arg1->value() && arg2->value();

	bool nandResult = !result;

	auto result_f = static_cast<Real::value_type>(nandResult ? 1 : 0);
	operandList.push(make_shared<Real>(result_f));
}
void Real::perform_Nor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = arg1->value() || arg2->value();

	bool nandResult = !result;

	auto result_f = static_cast<Real::value_type>(nandResult ? 1 : 0);
	operandList.push(make_shared<Real>(result_f));
}
void Real::perform_Or(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = arg1->value() || arg2->value();

	auto result_f = static_cast<Real::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Real>(result_f));
}

void Real::perform_Xnor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = (arg1->value() != 0) ^ (arg2->value() != 0);

	auto xnorResult = !result;

	auto result_f = static_cast<Real::value_type>(xnorResult ? 1 : 0);
	operandList.push(make_shared<Real>(result_f));
}
void Real::perform_Xor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = (arg1->value() != 0) ^ (arg2->value() != 0);

	auto result_f = static_cast<Real::value_type>(result ? 1 : 0);
	operandList.push(make_shared<Real>(result_f));
}
void Real::perform_Equality(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Real>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Real>(right)) {
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

void Real::perform_Inequality(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Real>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Real>(right)) {
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

void Real::perform_Greater(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Real>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Real>(right)) {
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

void Real::perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Real>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Real>(right)) {
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
void Real::perform_Less(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Real>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Real>(right)) {
			bool result = left_real->value() < right_real->value();
			operandList.push(make_shared<Boolean>(result));
		}
	}
	else
	{
		Real::value_type left_real_int = toRealValue(left);
		Real::value_type right_real_int = toRealValue(right);
		bool result = left_real_int <  right_real_int;
		operandList.push(make_shared<Boolean>(result));
	}
}
void Real::perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	if (auto left_real = std::dynamic_pointer_cast<Real>(left)) {
		if (auto right_real = std::dynamic_pointer_cast<Real>(right)) {
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
value_type fast_power(value_type base, value_type exponent)
{
	if (exponent.is_zero())
		return 1.0;
	auto x = fast_power(base, exponent / 2);
	if (fmod(exponent,2) == 0)
		return x * x;
	else
		return x * x * base;
}
value_type simple_power(value_type base, value_type exponent)
{
	value_type product = 1;
	for (value_type i = 0; i < exponent; ++i)
		product *= base;
	return product;
}
void Real::perform_Power(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	Real::value_type exponent = toRealValue(right);
	Real::value_type base = toRealValue(left);
	if (boost::multiprecision::floor(exponent) == exponent) {
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
	else {
		Real::value_type result = boost::multiprecision::pow(base, exponent);
		operandList.push(make_shared<Real>(result));
	}

	
}
void Real::perform_Pow(std::stack<std::shared_ptr<Operand>>& operandList) const
{

	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	Real::value_type exponent = toRealValue(right);
	Real::value_type base = toRealValue(left);
	Real::value_type result = boost::multiprecision::pow(base, exponent);
	
	operandList.push(make_shared<Real>(result));
	
	
}
void Real::perform_Floor(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = arg1->value();
	auto floorResult = boost::multiprecision::floor(result);
	
	operandList.push(make_shared<Real>(floorResult));
}
void Real::perform_Ceil(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto ceil_result = arg1->value();
	auto result = boost::multiprecision::ceil(ceil_result);
	
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Ln(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::log(arg1->value());
		
	operandList.push(make_shared<Real>(result));

	
}
void Real::perform_Lb(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::log2(arg1->value());
		
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Sqrt(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto arg1 = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto result = boost::multiprecision::sqrt(arg1->value());
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Min(std::stack<Operand::pointer_type>& operandList) const {
	auto arg2 = std::dynamic_pointer_cast<Real>(operandList.top());
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	Real::value_type right_value = toRealValue(right);
	Real::value_type left_value = toRealValue(left);

	Real::value_type result = (boost::multiprecision::min(left_value, right_value));

	operandList.push(std::make_shared<Real>(result));
	


}
void Real::perform_Max(std::stack<Operand::pointer_type>& operandList) const {
	
	auto right = operandList.top();
	operandList.pop();
	auto left = operandList.top();
	operandList.pop();

	Real::value_type right_value = toRealValue(right);
	Real::value_type left_value = toRealValue(left);

	Real::value_type result = (boost::multiprecision::max(left_value, right_value));

	operandList.push(std::make_shared<Real>(result));
}
void Real::perform_Abs(std::stack<Operand::pointer_type>& operandList) const {
	auto arg = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	Real::value_type arg_value = arg->value();
	Real::value_type result = boost::multiprecision::abs(arg_value);
	
	
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Arccos(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();
	
	auto double_y = y->value();
	
	auto result = boost::math::acosh(double_y);
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Arctan(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::atan(double_y);
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Arcsin(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::asin(double_y);
	operandList.push(make_shared<Real>(result));
}
void Real::perform_Exp(std::stack<std::shared_ptr<Operand>>& operandList) const
{
	auto y = std::dynamic_pointer_cast<Real>(operandList.top());
	operandList.pop();

	auto double_y = y->value();

	auto result = boost::multiprecision::exp(double_y);

	operandList.push(make_shared<Real>(result));
}
void Real::perform_Assignment(std::stack<Operand::pointer_type>& operandList) const {
	auto value = operandList.top();
	operandList.pop();

	auto variable = operandList.top();
	operandList.pop();

	auto variable_ptr = std::dynamic_pointer_cast<Variable>(variable);

	variable_ptr->set(value);

	operandList.push(variable_ptr);
}

