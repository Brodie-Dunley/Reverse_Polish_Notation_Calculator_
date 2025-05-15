/*!	\file	boolean.hpp
	\brief	Boolean classes implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementations of the Booleans classes derived from Operand.  Includes
the subclasses True and False.
=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019-11-05
	C++ 17 cleanup

Version 2012-11-13
	C++ 11 cleanup

Version 2009-11-26
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

#include <ee/boolean.hpp>
#include <ee/function.hpp>
#include <algorithm>


/*! Print a boolean token's value. */
Boolean::string_type Boolean::str() const {
	return value_ ? string_type("True") : string_type("False");
}

void Boolean::perform_Equality(std::stack<Operand::pointer_type>& operandList) const {

	if (operandList.size() < 2) {
		throw std::runtime_error("Error: Insufficient operands for equality operation");
	}

	// Pop the first operand
	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	if (!arg2) {
		throw std::runtime_error("Error: Operand 2 is not a Boolean");
	}

	// Pop the second operand
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	if (!arg1) {
		throw std::runtime_error("Error: Operand 1 is not a Boolean");
	}

	// Perform the equality operation
	auto result = (arg1->value() == arg2->value());

	// Push the result back onto the stack
	operandList.push(std::make_shared<Boolean>(result));

}

void Boolean::perform_Inequality(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();


	bool result = arg1->value() != arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}

void Boolean::perform_Greater(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();


	auto result = arg1->value() > arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}

void Boolean::perform_GreaterEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();


	auto result = arg1->value() >= arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}
void Boolean::perform_Less(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();


	auto result = arg1->value() < arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}
void Boolean::perform_LessEqual(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();


	auto result = arg1->value() <= arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}
void Boolean::perform_Not(std::stack<Operand::pointer_type>& operandList) const {

	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	
	bool result = !arg1->value();

	operandList.push(std::make_shared<Boolean>(result));
}
void Boolean::perform_And(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	bool result = arg1->value() && arg2->value();

	operandList.push(std::make_shared<Boolean>(result));
}
void Boolean::perform_Nand(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	bool result = arg1->value() && arg2->value();

	bool nandResult = !result;

	operandList.push(std::make_shared<Boolean>(nandResult));
}
void Boolean::perform_Nor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto result = arg1->value() || arg2->value();

	bool norResult = !result;

	operandList.push(std::make_shared<Boolean>(norResult));
}
void Boolean::perform_Or(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	

	bool result = arg1->value() || arg2->value();
	
	operandList.push(std::make_shared<Boolean>(result));
}

void Boolean::perform_Xnor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto result = (arg1->value() != 0) ^ (arg2->value() != 0);

	auto xnorResult = !result;

	operandList.push(std::make_shared<Boolean>(xnorResult));
}
void Boolean::perform_Xor(std::stack<Operand::pointer_type>& operandList) const {

	auto arg2 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();
	auto arg1 = std::dynamic_pointer_cast<Boolean>(operandList.top());
	operandList.pop();

	auto result = (arg1->value() != 0) ^ (arg2->value() != 0);
	auto result_f = static_cast<Boolean::value_type>(result ? 1 : 0);
	operandList.push(std::make_shared<Boolean>(result_f));
}

