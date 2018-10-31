/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 11:26:42 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/30 11:26:44 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <iostream>
# include "IOperand.hpp"
# include <regex>
# include <fstream>
# include <sstream>

static std::regex rules[] = {
	std::regex("(push|assert) (int8\\()(\\-)?[0-9]+(\\))(( )?(;)+(.)*)?"),
	std::regex("(push|assert) (int16\\()(\\-)?[0-9]+(\\))(( )?(;)+(.)*)?"),
	std::regex("(push|assert) (int32\\()(\\-)?[0-9]+(\\))(( )?(;)+(.)*)?"),
	std::regex("(push|assert) (float\\()(\\-)?[0-9]+.[0-9]+(\\))(( )?(;)+(.)*)?"),
	std::regex("(push|assert) (double\\()(\\-)?([0-9])+.([0-9])+(\\))(( )?(;)+(.)*)?"),
	std::regex("(pop|dump|add|sub|mul|div|mod|print|exit)(( )?(;)+(.)*)?"),

};

class Lexer {

public:

	Lexer(void);
	Lexer(const Lexer&);
	Lexer& operator=(const Lexer&);
	~Lexer(void);

	void analyze(std::string check, std::stringstream &input) const;

	class LexicalException : public std::exception {

		public:
			LexicalException(void);
			LexicalException(const LexicalException &src);
			virtual ~LexicalException(void) throw();
			LexicalException &operator=(const LexicalException &src);
			virtual const char *what() const throw();
	};

private:

};

#endif
