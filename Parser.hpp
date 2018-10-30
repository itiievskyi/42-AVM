/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:27:02 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/30 11:27:04 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <iostream>
# include "IOperand.hpp"
# include "Lexer.hpp"

enum eAction {
	PUSH = 101,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT,
	ERROR,
	EMPTY
};

class Parser {

public:

	Parser(void);
	Parser(const Parser&);
	Parser& operator=(const Parser&);
	~Parser(void);

	void parse(std::string line, bool stdinput, int count);
	eOperandType getType(void) const;
	eAction getAct(void) const;
	std::string getNum(void) const;

private:

	eAction			_act;
	eOperandType	_type;
	std::string		_num;
	std::string		_line;

};

#endif
