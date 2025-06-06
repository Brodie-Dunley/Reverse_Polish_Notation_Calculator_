/*!	\file	operator.cpp
	\brief	Operator classes implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementation of the Operator class derived from Token and the
supporting utilities.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ 11 cleanup

Version 0.1.0: 2010-11-08
	Added exception for assignment to a non-variable.

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

#include <ee/operator.hpp>
#include <ee/operand.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>
#include <cassert>
#include <deque>
#include <math.h>
#include <algorithm>


bool operator==(const std::string lhs, const Token::pointer_type& rhs)
{
	return lhs == rhs->str();
}
bool isOperator(const Token::pointer_type& token)
{
	
	static const std::vector<std::string> operatorList{
	"<Addition>","<Subtraction>","<Multiplication>","<Division>","<Factorial>","<Modulus>","<Power>","<Negation>","<Identity>","<Abs>","<Min>","<Max>","<Or>","<Assignment>","<And>","<Equality>","<Greater>","<GreaterEqual>","<Inequaltity>","<Less>","<LessEqual>","<Nand>","<Nor>","<Or>","<Xor>","<Xnor>","<Not>"
	};

	auto it = std::find(operatorList.begin(), operatorList.end(), token->str());
	if (it != operatorList.end())
		return true;
	else
		return false;
	
}

