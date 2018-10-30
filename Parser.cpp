/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:26:58 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/30 11:26:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) : _act(EMPTY), _type(Double), _num(""), _line("") {

	return;
}

Parser::Parser(Parser const &src) {

	*this = src;

	return;
}

Parser &Parser::operator=(Parser const &src) {

	static_cast <void>(src);

	return *this;
}

Parser::~Parser(void) {

	return;
}

void Parser::parse(std::string line, bool stdinput, int count) {
/*
	_line = line;

	static Lexer lexer = Lexer();
	try {
		lexer.analyze(line);
	}
	catch (Lexer::LexicalException &e) {
		std::cout << e.what() << "\033[1;33m" << count << "\033[0m"
		<< ": \033[1;31m" << _line << "\033[0m" << std::endl;
		_act = ERROR;
	}
*/
//	std::cout << "/* message */" << '\n';
	if (stdinput && line != "" && count) {}

}

eOperandType Parser::getType(void) const {

	return this->_type;
}

eAction Parser::getAct(void) const {

	return this->_act;
}

std::string Parser::getNum(void) const {

	return this->_num;
}
