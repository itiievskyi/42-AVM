/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperationExceptions.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:13:02 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/31 16:13:03 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperationExceptions.hpp"

// Empty Stack

EmptyStackException::EmptyStackException(void) {}

EmptyStackException::EmptyStackException(const EmptyStackException &src) {
	*this = src;
	return;
}

EmptyStackException::~EmptyStackException(void) throw() {}

EmptyStackException &EmptyStackException::operator=(const EmptyStackException &src) {
	static_cast <void> (src);
	return *this;
}

const char    *EmptyStackException::EmptyStackException::what() const throw() {
	return "Unable to proceed: the stack is empty";
}

// Non-printable

NonPrintableException::NonPrintableException(void) {}

NonPrintableException::NonPrintableException(const NonPrintableException &src) {
	*this = src;
	return;
}

NonPrintableException::~NonPrintableException(void) throw() {}

NonPrintableException &NonPrintableException::operator=(const NonPrintableException &src) {
	static_cast <void> (src);
	return *this;
}

const char    *NonPrintableException::NonPrintableException::what() const throw() {
	return "The top element is not of type Int8";
}

// Not Int8

NonInt8Exception::NonInt8Exception(void) : _line(0) {}

NonInt8Exception::NonInt8Exception(int line) : _line(line) {}

NonInt8Exception::NonInt8Exception(const NonInt8Exception &src) {
	*this = src;
	return;
}

NonInt8Exception::~NonInt8Exception(void) throw() {}

NonInt8Exception &NonInt8Exception::operator=(const NonInt8Exception &src) {
	static_cast <void> (src);
	return *this;
}

const char    *NonInt8Exception::NonInt8Exception::what() const throw() {
	std::string err = "The char #" + std::to_string(_line) + " is non-printable";
	return err.c_str();
}

// Assertion failed

AssertionException::AssertionException(void) {}

AssertionException::AssertionException(const AssertionException &src) {
	*this = src;
	return;
}

AssertionException::~AssertionException(void) throw() {}

AssertionException &AssertionException::operator=(const AssertionException &src) {
	static_cast <void> (src);
	return *this;
}

const char    *AssertionException::AssertionException::what() const throw() {
	return "Assertion failed";
}

// Less than 2 operands in the stack

LessThen2Exception::LessThen2Exception(void) {}

LessThen2Exception::LessThen2Exception(const LessThen2Exception &src) {
	*this = src;
	return;
}

LessThen2Exception::~LessThen2Exception(void) throw() {}

LessThen2Exception &LessThen2Exception::operator=(const LessThen2Exception &src) {
	static_cast <void> (src);
	return *this;
}

const char    *LessThen2Exception::LessThen2Exception::what() const throw() {
	return "Unable to proceed: there less than 2 operands in the stack";
}
