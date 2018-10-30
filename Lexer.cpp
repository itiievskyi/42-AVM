/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:26:49 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/30 11:26:51 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer(void) {

	return;
}

Lexer::Lexer(Lexer const &src) {

	*this = src;

	return;
}

Lexer &Lexer::operator=(Lexer const &src) {

	static_cast <void>(src);

	return *this;
}

Lexer::~Lexer(void) {

	return;
}

void Lexer::analyze(std::string line) const {

	bool error = true;

	for (std::size_t i = 0; i < (sizeof(rules) / sizeof(rules)[0]); i++) {
		if (std::regex_match(line, rules[i])) {
			error = false;
		}
	}

	if (!error) {
		std::cout << line << std::endl;
	} else {
		throw LexicalException();
	}
}

Lexer::LexicalException::LexicalException(void) {

	return;
}

Lexer::LexicalException::LexicalException(const LexicalException &src) {

	*this = src;

	return;
}

Lexer::LexicalException::~LexicalException(void) throw() {

	return;
}

Lexer::LexicalException &Lexer::LexicalException::operator=(const LexicalException &src) {

	static_cast <void> (src);

	return *this;
}

const char    *Lexer::LexicalException::what() const throw() {

	return "Lexical error in the line ";
}
