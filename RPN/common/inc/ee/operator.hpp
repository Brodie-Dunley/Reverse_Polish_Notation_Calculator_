#pragma once
/*!	\file	operator.hpp
	\brief	Operator classes declarations and utilities.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Operator classes derived from Token and the
supporting utilities.

	enum class Precedence
	DEF_PRECEDENCE()
	class Operator
		class BinaryOperator
			class RAssocOperator
				class Power
				class Assignment
			class LAssocOperator
				class Addition
				class And
				class Division
				class Equality
				class Greater
				class GreaterEqual
				class Inequality
				class Less
				class LessEqual
				class Multiplication
				class Modulus
				class Nand
				class Nor
				class Or
				class Subtraction
				class Xor
				class Xnor
		class NonAssociative
			class UnaryOperator
				class Identity
				class Negation
				class Not
			class PostfixOperator
				class Factorial

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated
	Converted 'enum' to 'enum class'

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2014.10.30
	Removed bitwise operators.

Version 2012.11.16
	Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 2012.11.13
	C++ 11 cleanup

Version 2010.11.09
	Switched boost::shared_ptr<> to std::shared_ptr<>.
	Added TOKEN_PTR_TYPE macro.

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

#include <ee/operand.hpp>
#include <ee/operation.hpp>
#include <ee/variable.hpp>
#include <boost/type_index.hpp>


/*! Operator Precedence values. */
enum class Precedence { MIN = 0,
	ASSIGNMENT, LOGOR, LOGXOR, LOGAND, BITOR,
	BITXOR, BITAND, EQUALITY, RELATIONAL, BITSHIFT,
	ADDITIVE, MULTIPLICATIVE, UNARY, POWER, POSTFIX,
	MAX };



/*! Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)\
	public: [[nodiscard]] Precedence precedence() const override { return Precedence::category; }




/*! Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	[[nodiscard]] virtual Precedence precedence() const = 0;
	virtual unsigned number_of_args() const = 0;
	virtual std::string associativeType() const = 0;
	
};

		/*! Binary operator token base class. */
		class BinaryOperator : public Operator {
		public:
			virtual std::string associativeType() const = 0;
			virtual std::string getName() const = 0;
			unsigned number_of_args() const override { return 2; }

		};

				/*! Right-associative operator base class. */
				class RAssocOperator : public BinaryOperator { 
					
				};

						/*! Power token. */
						class Power : public RAssocOperator {
						DEF_PRECEDENCE(POWER)
							std::string getName() const override { return "Power"; }
							
							std::string associativeType() const override { return "Right"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough o-perands on the stack for Power!" << std::endl;
									return;
								}
								operandList.top()->perform_Power(operandList);
							}
							
						};

						/*! Assignment token. */
						class Assignment : public RAssocOperator {
						DEF_PRECEDENCE(ASSIGNMENT)
							std::string getName() const override { return "Assignment"; }
							
							std::string associativeType() const override { return "Right"; }
						/*private:
							Variable::pointer_type target;
							Operand::pointer_type source;*/
						public:
							//Assignment(Variable::pointer_type const& target, Operand::pointer_type const& source) : target(target), source(source) {}
							void perform(std::stack<Operand::pointer_type>& operandList) const override {

								auto value = operandList.top();
								operandList.pop();
								

								auto variable = operandList.top();
								operandList.pop();


								if (auto variable_ptr = std::dynamic_pointer_cast<Variable>(variable))
								{
									variable_ptr->set(value);
									operandList.push(variable_ptr);
								}
								else
									throw std::runtime_error("Error: assignment to a non-variable.");
									
							}
							
						};


				/*! Left-associative operator base class. */
				class LAssocOperator : public BinaryOperator {
					
				};

						/*! Addition token. */
						class Addition : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
							std::string getName() const override { return "Addition"; }
							
							std::string associativeType() const override { return "Left"; }

						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 1)
								{
									std::cerr << "Not enough o-perands on the stack for addition!" << std::endl;
									return;
								}
								operandList.top()->perform_addition(operandList);
						}
						};

						/*! And token. */
						class And : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
							std::string getName() const override { return "And"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for And!" << std::endl;
									return;
								}
								operandList.top()->perform_And(operandList);
							}
						};

						/*! Division token. */
						class Division : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
							std::string getName() const override { return "Division"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough o-perands on the stack for Division!" << std::endl;
									return;
								}
								operandList.top()->perform_division(operandList);
							}
						};

						/*! Equality token. */
						class Equality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
							std::string getName() const override { return "Equality"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Equality!" << std::endl;
									return;
								}
								operandList.top()->perform_Equality(operandList);
							}
						};

						/*! Greater than token. */
						class Greater : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
							std::string getName() const override { return "Greater than"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Greater!" << std::endl;
									return;
								}
								operandList.top()->perform_Greater(operandList);
							}
						};

						/*! Greater than or equal to token. */
						class GreaterEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
							std::string getName() const override { return "Greater than or equal to"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for GreaterEqual!" << std::endl;
									return;
								}
								operandList.top()->perform_GreaterEqual(operandList);
							}
						};

						/*! Inequality operator token. */
						class Inequality : public LAssocOperator {
						DEF_PRECEDENCE(EQUALITY)
							std::string getName() const override { return "Inequality"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Inequality!" << std::endl;
									return;
								}
								operandList.top()->perform_Inequality(operandList);
							}
						};

						/*! Less than operator token. */
						class Less : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
							std::string getName() const override { return "Less than"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Less!" << std::endl;
									return;
								}
								operandList.top()->perform_Less(operandList);
							}
						};

						/*! Less than equal-to operator token. */
						class LessEqual : public LAssocOperator {
						DEF_PRECEDENCE(RELATIONAL)
							std::string getName() const override { return "Less than or equal to"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for LessEqual!" << std::endl;
									return;
								}
								operandList.top()->perform_LessEqual(operandList);
							}
						};

						/*! Multiplication operator token. */
						class Multiplication : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
							std::string getName() const override { return "Multiplication"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough o-perands on the stack for Multiplication!" << std::endl;
									return;
								}
								operandList.top()->perform_multiplication(operandList);
							}
						};

						/*! Modulus operator token. */
						class Modulus : public LAssocOperator {
						DEF_PRECEDENCE(MULTIPLICATIVE)
							std::string getName() const override { return "Modulus"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough o-perands on the stack for Modulus!" << std::endl;
									return;
								}
								operandList.top()->perform_Modulus(operandList);
							}
						};

						/*! Nand operator token. */
						class Nand : public LAssocOperator {
						DEF_PRECEDENCE(LOGAND)
							std::string getName() const override { return "Nand"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Nand!" << std::endl;
									return;
								}
								operandList.top()->perform_Nand(operandList);
							}
						};

						/*! Nor operator token. */
						class Nor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
							std::string getName() const override { return "Nor"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Nor!" << std::endl;
									return;
								}
								operandList.top()->perform_Nor(operandList);
							}
						};

						/*! Or operator token. */
						class Or : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
							std::string getName() const override { return "Or"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Or!" << std::endl;
									return;
								}
								operandList.top()->perform_Or(operandList);
							}
						};

						/*! Subtraction operator token. */
						class Subtraction : public LAssocOperator {
						DEF_PRECEDENCE(ADDITIVE)
							std::string getName() const override { return "Subtraction"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough o-perands on the stack for subtraction!" << std::endl;
									return;
								}
								operandList.top()->perform_subtraction(operandList);
							}
						};

						/*! XOR operator token. */
						class Xor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
							std::string getName() const override { return "XOR"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for xor!" << std::endl;
									return;
								}
								operandList.top()->perform_Xor(operandList);
							
							}
						};

						/*! XNOR operator token. */
						class Xnor : public LAssocOperator {
						DEF_PRECEDENCE(LOGOR)
							std::string getName() const override { return "XNOR"; }
							
							std::string associativeType() const override { return "Left"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 2)
								{
									std::cerr << "Not enough operands on the stack for Xnor!" << std::endl;
									return;
								}
								operandList.top()->perform_Xnor(operandList);
							}
						};


		/*! Non-associative operator token base class. */
		class NonAssociative : public Operator { 
		public:
			
		};

				/*! Unary operator token base class. */
				class UnaryOperator : public NonAssociative {
				public: [[nodiscard]] virtual unsigned number_of_args() const override { return 1; }
				DEF_PRECEDENCE(UNARY)
					//virtual std::string getName() const = 0;
				};

						/*! Identity operator token. */
						class Identity : public UnaryOperator {
							
							std::string associativeType() const override { return "None"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 1)
								{
									std::cerr << "Not enough o-perands on the stack for addition!" << std::endl;
									return;
								}
								operandList.top()->perform_Identity(operandList);
							}
						};

						/*! Negation operator token. */
						class Negation : public UnaryOperator {
							
							std::string associativeType() const override { return "None"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 1)
								{
									std::cerr << "Not enough o-perands on the stack for Negation!" << std::endl;
									return;
								}
								operandList.top()->perform_Negation(operandList);
							}
						};

						/*! Not operator token. */
						class Not : public UnaryOperator {
							
							std::string associativeType() const override { return "None"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
							
								if (operandList.size() < 1)
								{
									std::cerr << "Not enough operands on the stack for Not!" << std::endl;
									return;
								}
								operandList.top()->perform_Not(operandList);
							}
						};

				/*! Postfix Operator token base class. */
				class PostfixOperator : public UnaryOperator { 
					virtual unsigned number_of_args() const override { return 1; }
				};

						/*! Factorial token base class. */
						class Factorial : public PostfixOperator {
						public: [[nodiscard]] 
							  std::string associativeType() const override { return "None"; }
						public:
							void perform(std::stack<Operand::pointer_type>& operandList) const override {
								if (operandList.size() < 1)
								{
									std::cerr << "Not enough o-perands on the stack for addition!" << std::endl;
									return;
								}
								operandList.top()->perform_factorial(operandList);
							}
						};


						bool operator==(const std::string lhs, const Token::pointer_type& rhs);
						bool isOperator(const Token::pointer_type& token);
						