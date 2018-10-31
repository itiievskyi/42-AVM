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

	std::smatch sm;

	_line = line;

	// Parsing the operation type

	std::regex_match(line, sm, std::regex(
		"^(pop|dump|add|sub|mul|div|mod|print|exit|push|assert)(.)*"));
	if (sm[1] == "pop") {
		_act = POP;
	} else if (sm[1] == "dump") {
		_act = DUMP;
	} else if (sm[1] == "add") {
		_act = ADD;
	} else if (sm[1] == "sub") {
		_act = SUB;
	} else if (sm[1] == "mul") {
		_act = MUL;
	} else if (sm[1] == "div") {
		_act = DIV;
	} else if (sm[1] == "mod") {
		_act = MOD;
	} else if (sm[1] == "print") {
		_act = PRINT;
	} else if (sm[1] == "exit") {
		_act = EXIT;
	} else if (sm[1] == "push") {
		_act = PUSH;
	} else if (sm[1] == "assert") {
		_act = ASSERT;
	}

	// Parsing the number type & the number itself

	std::regex_match(line, sm, std::regex(
		"^(push|assert) (int8|int16|int32|float|double)(.)*"));
	if (sm[2] == "int8") {
		_type = Int8;
		std::regex_match(line, sm, std::regex(
			"^(push|assert) (int8\\()(\\-?[0-9]+)(\\))(( )?(;)+(.)*)?"));
		_num = sm[3];
	} else if (sm[2] == "int16") {
		_type = Int16;
		std::regex_match(line, sm, std::regex(
			"^(push|assert) (int16\\()(\\-?[0-9]+)(\\))(( )?(;)+(.)*)?"));
		_num = sm[3];
	} else if (sm[2] == "int32") {
		_type = Int32;
		std::regex_match(line, sm, std::regex(
			"^(push|assert) (int32\\()(\\-?[0-9]+)(\\))(( )?(;)+(.)*)?"));
		_num = sm[3];
	} else if (sm[2] == "float") {
		_type = Float;
		std::regex_match(line, sm, std::regex(
			"^(push|assert) (float\\()(\\-?[0-9]+.[0-9]+)(\\))(( )?(;)+(.)*)?"));
		_num = sm[3];
	} else if (sm[2] == "double") {
		_type = Double;
		std::regex_match(line, sm, std::regex(
			"^(push|assert) (double\\()(\\-?[0-9]+.[0-9]+)(\\))(( )?(;)+(.)*)?"));
		_num = sm[3];
	}

//	std::cout << "operation = '" << _act << "', type = '" << _type << "', num = '" << _num << "'"<< std::endl;

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
