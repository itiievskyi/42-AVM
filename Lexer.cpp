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

void Lexer::analyze(std::string check, char *path) const {

	std::string line;
	std::stringstream _error;

	std::ifstream filestream(path);

	// Line-by-line check for error messages collection

	while (!(filestream.eof())) {
		bool error = true;

		static int count = 0;
		++count;

		// Skipping empty lines and comments
		std::getline (filestream, line);
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
		}
	}

	// Checking for 'exit' command

	if (!std::regex_search(check, std::regex("(^|\\n)+exit(( )?(;)+(.)*)?"))) {
		_error << "\033[1;33m" << "\tThere is no 'exit' command" << "\033[0m"
		<< std::endl;
	}

	// Checking for errors presense and raising an exception

	if (_error.good() && _error.str().size() > 0) {
		std::cout << "The following lexical errors were found: " << std::endl;
		std::cout << _error.rdbuf();
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

	return "";
}
