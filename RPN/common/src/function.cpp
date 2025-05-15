/*!	\file	function.cpp
	\brief	Function class implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Function classes derived from Operation.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2014.10.30
	Removed binary function

Version 2012.11.13
	C++ 11 cleanup

Version 2009.11.26
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


#include <ee/function.hpp>
#include <ee/integer.hpp>
#include <map>
#include <typeinfo>
#include <math.h>

using dd_Operation = std::function<Integer::value_type(int, int)>;
using f_Operation = std::function<Integer::value_type(int)>;

std::map<std::string, dd_Operation> double_functions = {
	{"<Min>", [](int a, int b) {return std::min(a,b); }},
	{"<Max>", [](int a, int b) {return std::max(a,b); }},
	{"<Pow>", [](int a, int b) {return static_cast<int>(pow(a,b)); }}



};
std::map<std::string, f_Operation> single_functions = {
	{"<Abs>",[](int a) {return static_cast<Integer::value_type>(abs(a)); }}

};
bool isFunction(const Token::pointer_type& token)
{
	static const std::vector<std::string> functionList{
		"<Min>" ,"<Max>","<Abs>","<Pow>","<Arccos>","<Arcsin>","<Arctan>","<Ceil>","<Cos>","<Sin>","<Tan>","<Exp>","<Floor>","<Lb>", "<Ln>", "<Log>","<Result>","<Sqrt>","<Arctan2>"
	};

	auto it = std::find(functionList.begin(), functionList.end(), token->str());
	if (it != functionList.end())
		return true;

	return false;
}



