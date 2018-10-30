/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:31:43 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/25 16:31:44 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_H
# define ABSTRACTVM_H

# include "Operand.tpp"
# include "Factory.hpp"
# include "Parser.hpp"
# include <iostream>
# include <sstream>
# include <fstream>
# include <iomanip>
# include <vector>
# include <stack>

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
