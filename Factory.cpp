/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:19:51 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/25 11:19:52 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.tpp"
#include <string>
#include <limits>
#include <cfloat>

Factory::Factory(void) {

	this->_funcs[0] = &Factory::createInt8;
	this->_funcs[1] = &Factory::createInt16;
	this->_funcs[2] = &Factory::createInt32;
	this->_funcs[3] = &Factory::createFloat;
	this->_funcs[4] = &Factory::createDouble;

	return;
}

Factory::Factory(Factory const &src) {

	*this = src;

	return;
}

Factory &Factory::operator=(Factory const &src) {

	static_cast <void>(src);

	return *this;
}

Factory::~Factory(void) {

	return;
}

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const {

		long long test = std::stod(value);
		if (type == Int8 && (test > INT8_MAX || test < INT8_MIN)) {
			throw Factory::CreationOutOfRangeExceprion("Int8", value);
		} else if (type == Int16 && (test > INT16_MAX || test < INT16_MIN)) {
			throw Factory::CreationOutOfRangeExceprion("Int16", value);
		} else if (type == Int32 && (test > INT32_MAX || test < INT32_MIN)) {
			throw Factory::CreationOutOfRangeExceprion("Int32", value);
		} else if (type == Float && (test > FLT_MAX || test < -FLT_MAX)) {
			throw Factory::CreationOutOfRangeExceprion("Float", value);
		} else if (type == Double && (test > DBL_MAX || test < -DBL_MAX)) {
			throw Factory::CreationOutOfRangeExceprion("Double", value);
		}

	return (this->*_funcs[type])(value);
}

IOperand const *Factory::createInt8(std::string const &value) const {
	return (new Operand<int8_t>(std::stoi(value)));
}

IOperand const *Factory::createInt16(std::string const &value) const {
	return (new Operand<int16_t>(std::stoi(value)));
}

IOperand const *Factory::createInt32(std::string const &value) const {
	return (new Operand<int32_t>(std::stoi(value)));
}

IOperand const *Factory::createFloat(std::string const &value) const {
	return (new Operand<float>(std::stof(value)));
}

IOperand const *Factory::createDouble(std::string const &value) const {
	return (new Operand<double>(std::stod(value)));
}

Factory::CreationOutOfRangeExceprion::CreationOutOfRangeExceprion(void) {

	return;
}

Factory::CreationOutOfRangeExceprion::CreationOutOfRangeExceprion(
std::string type, std::string const &value) : _value(value), _type(type) {

	return;
}

Factory::CreationOutOfRangeExceprion::CreationOutOfRangeExceprion(
	const CreationOutOfRangeExceprion &src) {

	*this = src;

	return;
}

Factory::CreationOutOfRangeExceprion::~CreationOutOfRangeExceprion(void) throw() {

	return;
}

Factory::CreationOutOfRangeExceprion &Factory::CreationOutOfRangeExceprion::operator=(
	const CreationOutOfRangeExceprion &src) {

	static_cast <void> (src);

	return *this;
}

const char    *Factory::CreationOutOfRangeExceprion::what() const throw() {

	std::string error = "Object of type " + _type +
	" can't be created with the value " + _value + " due to overflow or underflow";

	return error.c_str();
}
