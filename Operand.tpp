/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 14:53:24 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/23 14:53:38 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_T
# define OPERAND_T

# include <iostream>
# include <sstream>
# include <fstream>
# include <iomanip>
# include <exception>
# include <limits>
# include <cmath>
# include <cfloat>
# include "IOperand.hpp"

# ifndef OPERAND_T_DEFINED
	#  define OPERAND_T_DEFINED
		template<typename T> class Operand;
	#  include "Factory.hpp"
# endif

template <typename T>
class Operand : public IOperand {

public:

	Operand(void) {
		this->_value = std::to_string(static_cast<T>(0));
		this->_type = Int32;
	}

	Operand(T value) {
		if (this->getType() == Float) {
			std::ostringstream temp;
			temp << value;
			this->_value = temp.str();
		} else if (this->getType() == Double) {
			std::ostringstream temp;
			temp << value;
			this->_value = temp.str();
		} else {
			this->_value = std::to_string(value);
		}
	}

	Operand(Operand const &obj) {
		*this = obj;
	}

	Operand &operator=(Operand const &rhs) {
		this->_value = rhs._value;
		return *this;
	}

	~Operand(void) {
		return;
	}

	class OperationOverflowException : public std::exception {
		public:
			OperationOverflowException(std::string op, double v1, double v2, std::string type) :
				_op(op), _v1(v1), _v2(v2), _type(type) {}
			OperationOverflowException(const OperationOverflowException &src) {
				*this = src;
			}
			virtual ~OperationOverflowException(void) throw() {}
			OperationOverflowException  &operator=(const OperationOverflowException &src) {
				static_cast <void> (src);
				return *this;
			}
			virtual const char *what() const throw() {
				std::stringstream ss;
				ss << "Breaking the limits of type " << _type <<
				": '(" << _v1 << ") " << _op << " (" << _v2 << ")'";

				std::string error = "" + ss.str() + "";
				return error.c_str();
			}

		private:
			std::string	_op;
			double		_v1;
			double		_v2;
			std::string	_type;
	};

	class ZeroDivisionException : public std::exception {
		public:
			ZeroDivisionException(std::string op, double v1, double v2) :
				_op(op), _v1(v1), _v2(v2) {}
			ZeroDivisionException(const ZeroDivisionException &src) {
				*this = src;
			}
			virtual ~ZeroDivisionException(void) throw() {}
			ZeroDivisionException  &operator=(const ZeroDivisionException &src) {
				static_cast <void> (src);
				return *this;
			}
			virtual const char *what() const throw() {
				std::stringstream ss;
				ss << "Division or modulo by 0: '(" << _v1 << ") " << _op << " ("
				<< _v2 << ")'";

				std::string error = "" + ss.str() + "";
				return error.c_str();
			}

		private:
			std::string	_op;
			double		_v1;
			double		_v2;
	};

	int getPrecision(void) const;
	eOperandType getType(void) const;

	void checkOperationOverflow(char op, double v1, double v2, eOperandType type) const {
		long double result;

		switch (op) {
			case '+':
				result = v1 + v2;
				if (type == Int8 && (result > INT8_MAX || result < INT8_MIN)) {
					throw OperationOverflowException("+", v1, v2, "Int8");
				} else if (type == Int16 && (result > INT16_MAX || result < INT16_MIN)) {
					throw OperationOverflowException("+", v1, v2, "Int16");
				} else if (type == Int32 && (result > INT32_MAX || result < INT32_MIN)) {
					throw OperationOverflowException("+", v1, v2, "Int32");
				} else if (type == Float && (result > FLT_MAX || result < -FLT_MAX)) {
					throw OperationOverflowException("+", v1, v2, "Float");
				} else if (type == Double && (result > DBL_MAX || result < -DBL_MAX)) {
					throw OperationOverflowException("+", v1, v2, "Double");
				}
				break;
			case '-':
				result = v1 - v2;
				if (type == Int8 && (result > INT8_MAX || result < INT8_MIN)) {
					throw OperationOverflowException("-", v1, v2, "Int8");
				} else if (type == Int16 && (result > INT16_MAX || result < INT16_MIN)) {
					throw OperationOverflowException("-", v1, v2, "Int16");
				} else if (type == Int32 && (result > INT32_MAX || result < INT32_MIN)) {
					throw OperationOverflowException("-", v1, v2, "Int32");
				} else if (type == Float && (result > FLT_MAX || result < -FLT_MAX)) {
					throw OperationOverflowException("-", v1, v2, "Float");
				} else if (type == Double && (result > DBL_MAX || result < -DBL_MAX)) {
					throw OperationOverflowException("-", v1, v2, "Double");
				}
				break;
			case '*':
				result = v1 * v2;
				if (type == Int8 && (result > INT8_MAX || result < INT8_MIN)) {
					throw OperationOverflowException("*", v1, v2, "Int8");
				} else if (type == Int16 && (result > INT16_MAX || result < INT16_MIN)) {
					throw OperationOverflowException("*", v1, v2, "Int16");
				} else if (type == Int32 && (result > INT32_MAX || result < INT32_MIN)) {
					throw OperationOverflowException("*", v1, v2, "Int32");
				} else if (type == Float && (result > FLT_MAX || result < -FLT_MAX)) {
					throw OperationOverflowException("*", v1, v2, "Float");
				} else if (type == Double && (result > DBL_MAX || result < -DBL_MAX)) {
					throw OperationOverflowException("*", v1, v2, "Double");
				}
				break;
			case '/':
				if (v2 == 0) {
					throw ZeroDivisionException("/", v1, v2);
					return;
				}
				result = v1 / v2;
				if (type == Int8 && (result > INT8_MAX || result < INT8_MIN)) {
					throw OperationOverflowException("/", v1, v2, "Int8");
				} else if (type == Int16 && (result > INT16_MAX || result < INT16_MIN)) {
					throw OperationOverflowException("/", v1, v2, "Int16");
				} else if (type == Int32 && (result > INT32_MAX || result < INT32_MIN)) {
					throw OperationOverflowException("/", v1, v2, "Int32");
				} else if (type == Float && (result > FLT_MAX || result < -FLT_MAX)) {
					throw OperationOverflowException("/", v1, v2, "Float");
				} else if (type == Double && (result > DBL_MAX || result < -DBL_MAX)) {
					throw OperationOverflowException("/", v1, v2, "Double");
				}
				break;
			case '%':
				if (v2 == 0) {
					throw ZeroDivisionException("%", v1, v2);
					return;
				}
				result = std::fmod(v1, v2);
				if (type == Int8 && (result > INT8_MAX || result < INT8_MIN)) {
					throw OperationOverflowException("%", v1, v2, "Int8");
				} else if (type == Int16 && (result > INT16_MAX || result < INT16_MIN)) {
					throw OperationOverflowException("%", v1, v2, "Int16");
				} else if (type == Int32 && (result > INT32_MAX || result < INT32_MIN)) {
					throw OperationOverflowException("%", v1, v2, "Int32");
				} else if (type == Float && (result > FLT_MAX || result < -FLT_MAX)) {
					throw OperationOverflowException("%", v1, v2, "Float");
				} else if (type == Double && (result > DBL_MAX || result < -DBL_MAX)) {
					throw OperationOverflowException("%", v1, v2, "Double");
				}
				break;
		}
	}

	IOperand const *operator+(IOperand const &rhs) const {
		double v1 = (stod(this->_value));
		double v2 = (stod(rhs.toString()));

		eOperandType newType =
		(this->getType() < rhs.getType() ? rhs.getType() : this->getType());
		this->checkOperationOverflow('+', v1, v2, newType);
		IOperand const *ret;

		Factory *factory = new Factory();
		ret = factory->createOperand(newType, std::to_string(v1 + v2));
		delete factory;

		return ret;
	}

	IOperand const *operator-(IOperand const &rhs) const {
		double v1 = (stod(this->_value));
		double v2 = (stod(rhs.toString()));

		eOperandType newType =
		(this->getType() < rhs.getType() ? rhs.getType() : this->getType());
		this->checkOperationOverflow('-', v1, v2, newType);
		IOperand const *ret;

		Factory *factory = new Factory();
		ret = factory->createOperand(newType, std::to_string(v1 - v2));
		delete factory;

		return ret;
	}

	IOperand const *operator*(IOperand const &rhs) const {
		double v1 = (stod(this->_value));
		double v2 = (stod(rhs.toString()));

		eOperandType newType =
		(this->getType() < rhs.getType() ? rhs.getType() : this->getType());
		this->checkOperationOverflow('*', v1, v2, newType);
		IOperand const *ret;

		Factory *factory = new Factory();
		ret = factory->createOperand(newType, std::to_string(v2 * v1));
		delete factory;

		return ret;
	}

	IOperand const *operator/(IOperand const &rhs) const {
		double v1 = (stod(this->_value));
		double v2 = (stod(rhs.toString()));

		eOperandType newType =
		(this->getType() < rhs.getType() ? rhs.getType() : this->getType());
		this->checkOperationOverflow('/', v1, v2, newType);
		IOperand const *ret;

		Factory *factory = new Factory();
		ret = factory->createOperand(newType, std::to_string(v1 / v2));
		delete factory;

		return ret;
	}

	IOperand const *operator%(IOperand const &rhs) const {
		double v1 = (stod(this->_value));
		double v2 = (stod(rhs.toString()));

		eOperandType newType =
		(this->getType() < rhs.getType() ? rhs.getType() : this->getType());
		this->checkOperationOverflow('%', v1, v2, newType);
		IOperand const *ret;

		Factory *factory = new Factory();
		ret = factory->createOperand(newType, std::to_string(std::fmod(v1, v2)));
		delete factory;

		return ret;
	}

	std::string const & toString(void) const {
		return this->_value;
	}

private:

	std::string		_value;
	eOperandType	_type;

};

#endif
