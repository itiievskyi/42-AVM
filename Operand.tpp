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
		this->_value = std::to_string(value);
	}

	Operand(std::string str) {
		this->_value = std::to_string(static_cast<T>(stod(str)));
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

	class AddOverflowException : public std::exception {
		public:
			AddOverflowException(void) {}
			AddOverflowException(const AddOverflowException &src) {
				*this = src;
			}
			virtual ~AddOverflowException(void) throw() {}
			AddOverflowException  &operator=(const AddOverflowException &src) {
				static_cast <void> (src);
				return *this;
			}
			virtual const char *what() const throw() {
				return "ERROR: An operation on two operands causes an overflow";
			}
	};

	int getPrecision(void) const;
	eOperandType getType(void) const;

	IOperand const *operator+(IOperand const &rhs) const {
		double v1 = (stod(this->_value));
		double v2 = (stod(rhs.toString()));
		try {
			if (INT_MAX - v1 < v2) {
				throw AddOverflowException();
			}
		}
		catch(Operand::AddOverflowException &e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}
		IOperand const *ret;
		if (this->getPrecision() < rhs.getPrecision()) {
			return (rhs + *this);
		} else {
			Factory *factory = new Factory();
			ret = factory->createOperand(this->getType(), std::to_string(v1 + v2));
			delete factory;
		}
		return ret;
	}

	IOperand const *operator-(IOperand const &rhs) const {
		if (&rhs != nullptr) {}
		return nullptr;
	}

	IOperand const *operator*(IOperand const &rhs) const {
		if (&rhs != nullptr) {}
		return nullptr;
	}

	IOperand const *operator/(IOperand const &rhs) const {
		if (&rhs != nullptr) {}
		return nullptr;
	}

	IOperand const *operator%(IOperand const &rhs) const {
		if (&rhs != nullptr) {}
		return nullptr;
	}

	std::string const & toString(void) const {
		return this->_value;
	}

private:

	std::string		_value;
	eOperandType	_type;

};

#endif
