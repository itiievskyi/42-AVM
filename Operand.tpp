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

	int getPrecision(void) const;
	eOperandType getType(void) const;

	IOperand const *operator+(IOperand const &rhs) const {
		if (this->getPrecision() < rhs.getPrecision())
			return (rhs + *this);
	//	T lhs_value = static_cast<T>(stod(this->_value));
		T rhs_value = static_cast<T>(stod(rhs.toString()));
	//	add_flow_check<T>(lhs_value, rhs_value);
		Factory *factory = new Factory();
		IOperand const * ret_val = factory->createOperand(this->getType(), std::to_string(static_cast<T>(stod(this->_value)) + rhs_value));
		delete factory;
		return ret_val;
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
	Factory			*_factory;

};

#endif
