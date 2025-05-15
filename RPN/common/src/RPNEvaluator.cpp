/*!	\file	RPNEvaluator.cpp
	\brief	RPN Evaluator class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated
	Changed to GATS_TEST

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.10
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

#include <ee/RPNEvaluator.hpp>
#include <ee/integer.hpp>
#include <ee/operation.hpp>
#include <ee/operator.hpp>
#include <ee/function.hpp>
#include <ee/real.hpp>
#include <cassert>
#include <stack>
#include <unordered_map>
#include <ee/variable.hpp>
#include <boost/multiprecision/debug_adaptor.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/type_index.hpp>




[[nodiscard]] Operand::pointer_type RPNEvaluator::evaluate(TokenList const& rpnExpression) {

	bool storeResults = false;
	Result resultClass;
	if (rpnExpression.empty()) {
		throw std::runtime_error("Error: insufficient operands");
	}
	std::stack<Operand::pointer_type> operandStack;
	
	for (const auto& token : rpnExpression)
	{
		
		if (auto operandToken = std::dynamic_pointer_cast<Operand>(token)) {
			operandStack.push(operandToken);
		}
		else if (auto operatorToken = std::dynamic_pointer_cast<Operator>(token)) {

			operatorToken->perform(operandStack);

		}
		else if (auto functionToken = std::dynamic_pointer_cast<Function>(token))
		{
			if (operandStack.size() < functionToken->number_of_args())
				throw std::runtime_error("Error: insufficient operands for operator");

			if (functionToken->str() == "<Result>")
				storeResults = true;
			functionToken->perform(operandStack);
			
		}
		else {
			throw std::runtime_error("Error: Unsupported token type");
		}
			
	}
	
	if (operandStack.size() != 1) {
		throw std::runtime_error("Error: too many operands");
	}

	auto final_result = operandStack.top();
	
	operandStack.pop();
	
	return final_result;

}

