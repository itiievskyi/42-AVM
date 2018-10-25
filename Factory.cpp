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
	return (new Operand<float>(std::stoi(value)));
}

IOperand const *Factory::createDouble(std::string const &value) const {
	return (new Operand<double>(std::stoi(value)));
}
