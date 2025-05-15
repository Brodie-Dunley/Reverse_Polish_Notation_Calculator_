/*!	\file	parser.cpp
	\brief	Parser class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han
=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated
	Changed to GATS_TEST

Version 2014.10.31
	Visual C++ 2013

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.02
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

#include <ee/parser.hpp>
#include <ee/function.hpp>
#include <ee/operand.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <ee/real.hpp>
#include <stack>
#include <queue>
#include <unordered_map>

auto get_infix_eval() {
	return std::unordered_map<std::string, std::function<void(TokenList&, std::stack<std::shared_ptr<Token>>&, std::shared_ptr<Token>)>>{
		{"<LeftParenthesis>", [](TokenList& tokenList, std::stack<std::shared_ptr<Token>>& operator_stack, std::shared_ptr<Token> token) {
			operator_stack.push(token);
			}},
		{ "<RightParenthesis>", [](TokenList& tokenList, std::stack<std::shared_ptr<Token>>& operator_stack, std::shared_ptr<Token> token) {
			while (!operator_stack.empty() && operator_stack.top()->str() != "<LeftParenthesis>") {
				tokenList.push_back(operator_stack.top());
				operator_stack.pop();
			}
			if (operator_stack.empty()) {
				throw std::runtime_error("Mismatched parentheses");
			}

			// Pop the left parenthesis
			operator_stack.pop();

			// Handle functions on top of the stack
			if (!operator_stack.empty()) {
				auto topToken = operator_stack.top();
				if (isFunction(topToken)) {
					tokenList.push_back(topToken);
					operator_stack.pop();
				}
			}
		} },
		{ "<Not>",[](TokenList& tokenList, std::stack<std::shared_ptr<Token>>& operator_stack, std::shared_ptr<Token> token) {
			
			while (!operator_stack.empty()) {
				auto stack_top = std::dynamic_pointer_cast<Operator>(operator_stack.top());
				auto op = std::dynamic_pointer_cast<Operator>(token);
				if (!stack_top || stack_top->precedence() < op->precedence())
					break;

				tokenList.push_back(operator_stack.top());
				operator_stack.pop();
				}
			operator_stack.push(token);
			} },
		{ "<And>",[](TokenList& tokenList, std::stack<std::shared_ptr<Token>>& operator_stack, std::shared_ptr<Token> token) {

					while (!operator_stack.empty()) {
						auto stack_top = std::dynamic_pointer_cast<Operator>(operator_stack.top());
						auto op = std::dynamic_pointer_cast<Operator>(token);
						if (!stack_top || stack_top->precedence() < op->precedence())
							break;

						tokenList.push_back(operator_stack.top());
						operator_stack.pop();
						}
					operator_stack.push(token);
		} },


		{ "<Addition>", push_operation },
		{ "<Subtraction>", push_operation },
		{ "<Multiplication>", push_operation },
		{ "<Division>", push_operation },
		{ "<Factorial>", push_operation },
		{ "<Modulus>", push_operation },
		{ "<Power>", push_operation },
		{ "<Negation>", push_operation },
		{ "<Abs>", push_operation },
		{ "<Min>", push_operation },
		{ "<Max>", push_operation },
		{"<Identity>", push_operation },
		{"<ArgumentSeparator>",push_operation },
		{"True",push_operation },
		{ "False",push_operation },
		{ "<Or>", push_operation },
		{ "<Xor>", push_operation },
		{ "<Nand>", push_operation },
		{ "<Nor>", push_operation },
		{ "<Xnor>", push_operation },
		{ "<Sin>", push_operation },
		{ "<Cos>", push_operation },
		{ "<Tan>", push_operation },
		{ "<Arctan2>", push_operation },
		{ "<Pow>", push_operation },
		{ "<Arccos>", push_operation },
		{ "<Arcsin>", push_operation },
		{ "<Arctan>", push_operation },
		{ "<Floor>", push_operation },
		{ "<Ceil>", push_operation },
		{ "<Exp>", push_operation },
		{ "<Lb>", push_operation },
		{ "<Ln>", push_operation },
		{ "<Sqrt>", push_operation },
		{ "<Equality>", push_operation },
		{ "<Inequality>", push_operation },
		{ "<Less>", push_operation },
		{ "<LessEqual>", push_operation },
		{ "<Greater>", push_operation },
		{ "<GreaterEqual>", push_operation },
		{ "<Assignment>", push_operation }

	};
}

void push_operation(TokenList& tokenList, std::stack<std::shared_ptr<Token>>& operator_stack, std::shared_ptr<Token> token)
{

	if (auto op = std::dynamic_pointer_cast<Operator>(token))
	{
		while (!operator_stack.empty())
		{
			auto stack_top = std::dynamic_pointer_cast<Operator>(operator_stack.top());
			if (!stack_top)
				break;
			/*if (!isOperator(operator_stack.top()))
				break;*/

			if ((op->associativeType() == "Left" && op->precedence() <= stack_top->precedence()) || (op->associativeType() == "Right" && op->precedence() < stack_top->precedence())) {
				tokenList.push_back(operator_stack.top());
				operator_stack.pop();

			}
			else
				break;
		}
		operator_stack.push(token);
	}
	else if (auto op = std::dynamic_pointer_cast<Function>(token))
	{
		operator_stack.push(op);
	}
	else if (auto op = std::dynamic_pointer_cast<ArgumentSeparator>(token))
	{
		while (operator_stack.top()->str() != "<LeftParenthesis>")
		{
			tokenList.push_back(operator_stack.top());
			operator_stack.pop();
		}
	}
	
}

[[nodiscard]] TokenList Parser::parse(TokenList const& infixTokens) {


	TokenList tokenList{};
	std::stack<std::shared_ptr<Token>> operator_stack{};

	auto infixEval = get_infix_eval();
	for (const auto& infix : infixTokens)
	{
		std::string current_token = infix->str();

		if (auto operandToken = dynamic_pointer_cast<Operand>(infix))
		{
			tokenList.push_back(operandToken);
		}
		else if (auto functionToken = dynamic_pointer_cast<Function>(infix))
		{
			push_operation(tokenList, operator_stack, functionToken);
		}
		else {
			auto eval_it = infixEval.find(current_token);
			if (eval_it != infixEval.end()) {
				eval_it->second(tokenList, operator_stack, infix);
			}
			else
				throw std::runtime_error("Unknown token: " + current_token);
		}
	}
	
	
	while (!operator_stack.empty())
	{
		if (operator_stack.top()->str() == "<LeftParenthesis>")
			throw std::runtime_error("Missing right parenthesis");

		tokenList.emplace_back(operator_stack.top());
		operator_stack.pop();
	}
	
	return tokenList;
}


