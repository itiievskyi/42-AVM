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

Lexer::Lexer(void) :_len(48) {

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

void Lexer::analyze(std::string check, std::stringstream &input) {

	std::string line;
	std::stringstream _error;

	// Line-by-line check for error messages collection

	while (!(input.eof())) {
		bool error = true;

		static int count = 0;
		++count;

		// Skipping empty lines and comments
		std::getline (input, line);
		if (line.empty() || line[0] == ';') {
			continue;
		}

		for (std::size_t i = 0; i < (sizeof(rules) / sizeof(rules)[0]); i++) {

			if (std::regex_match(line, rules[i])) {
				error = false;
			}
		}
		if (error) {
			_error << "\tLine " << "\033[1;33m" << count << "\033[0m" << ": "
			<< "\033[1;31m" << line << "\033[0m" << std::endl;
			int newLen = line.length() + 15 + std::to_string(count).length();
			if (newLen > this->_len && newLen <= 80) {
				this->_len = newLen;
			}
		}
	}

	// Checking for 'exit' command

	if (!std::regex_search(check, std::regex("(^|\\n)+exit(( )?(;)+(.)*)?"))) {
		_error << "\033[1;33m" << "\tThere is no 'exit' command" << "\033[0m"
		<< std::endl;
	}

	// Checking for errors presense and raising an exception

	if (_error.good() && _error.str().size() > 0) {
		for (int i = 0; i < _len; i++) {
			std::cout << "\xe2\x95\x90";
		}
		std::cout << std::endl << "\033[1;32m" <<
		"The following lexical errors were found: " << "\033[0m" << std::endl;
		std::cout << _error.rdbuf();
		throw LexicalException();
	}
}

int Lexer::getLen(void) const {

	return this->_len;
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

	return "";
}
