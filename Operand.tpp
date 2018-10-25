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
# include "IOperand.hpp"

template <class T>
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
/*
	IOperand const *operator+(IOperand const &rhs) const {

	}

	IOperand const *operator-(IOperand const &rhs) const {

	}

	IOperand const *operator*(IOperand const &rhs) const {

	}

	IOperand const *operator/(IOperand const &rhs) const {

	}

	IOperand const *operator%(IOperand const &rhs) const {

	}
*/
	std::string const & toString(void) const {
		return this->_value;
	}

private:

	int		_value;
	int		_type;

};

template<> int Operand<int8_t>::getPrecision(void) const {
	return Int8;
}

template<> eOperandType Operand<int8_t>::getType(void) const {
	return Int8;
}

template<> int Operand<int16_t>::getPrecision(void) const {
	return Int16;
}

template<> eOperandType Operand<int16_t>::getType(void) const {
	return Int16;
}

template<> int Operand<int32_t>::getPrecision(void) const {
	return Int32;
}

template<> eOperandType Operand<int32_t>::getType(void) const {
	return Int32;
}

template<> int Operand<float>::getPrecision(void) const {
	return Float;
}

template<> eOperandType Operand<float>::getType(void) const {
	return Float;
}

template<> int Operand<double>::getPrecision(void) const {
	return Double;
}

template<> eOperandType Operand<double>::getType(void) const {
	return Double;
}

#endif
