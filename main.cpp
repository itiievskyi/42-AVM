/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 18:35:34 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/11 18:35:36 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"
#include <cstdlib>

void placeFileErrorMsg(std::string msg, std::string path) {
	int len = 9 + path.length() + msg.length();
	for (int i = 0; (i < len && i < 80); i++) {
		std::cout << "\xe2\x95\x90";
	}
	std::cout << std::endl;
	std::cout << "\033[1;31m" << "ERROR: " << "\033[0m"
	<< path << ": " << "\033[1;33m"
	<< msg << "\033[0m" << std::endl;
	for (int i = 0; (i < len && i < 80); i++) {
		std::cout << "\xe2\x95\x90";
	}
	std::cout << std::endl;
}

int main(int argc, char **argv) {

	std::list<const IOperand *> avmStack;

	std::string line;
	eAction action = EMPTY;
	static int count = 0;
	bool stdinput = false;

	std::ifstream filestream;
	std::stringstream lexerInput;
	std::stringstream parserInput;
	std::string check;

	Factory fact = Factory();
	Parser parser = Parser();
	Lexer lexer = Lexer();

	if (argc == 1) {
		while (!(std::cin.eof()) && line != ";;") {
			std::getline(std::cin, line);
			lexerInput << line << std::endl;
			parserInput << line << std::endl;
		}
		// Checking for ctrl+D input interruption
		if (line != ";;") {
			std::cout << "═══════════════════════════════════════════════════"
			<< std::endl << "\033[1;31m" <<
			"ERROR: The input was interrupted by pressing Ctrl+D" << std::endl
			<< "or file with the standard syntax was passed to pipe" << std::endl
			<< "\033[1;33m" << "Use ';;' command at the start of a line instead"
			<< "\033[0m" << std::endl <<
			"═══════════════════════════════════════════════════" << std::endl;
			return -1;
		}
		check = lexerInput.str();
	} else if (argc == 2) {
		// Checking for ctrl+D uncatchable errors with /dev/ paths
		std::regex path_short("(/dev)");
		std::regex path_long("(/dev/)+(.)*");
		if (std::regex_match(std::string(argv[1]), path_short) ||
			std::regex_match(std::string(argv[1]), path_long)) {
			placeFileErrorMsg((std::string("Bad path specified. It's strictly ")
			+ std::string("forbidden to use /dev/ \n\tpath to place AVM files in")),
			std::string(argv[1]));
			return -1;
		}
		filestream.open(argv[1]);
		// Checking for errors while opening
		try {
			filestream.exceptions(std::ios::failbit | std::ios::badbit);
			filestream.seekg(0, std::ios::end);
		} catch (std::ios_base::failure &err) {
			placeFileErrorMsg(
				std::string(std::strerror(errno)), std::string(argv[1]));
			return -1;
		}
		// Checking for directory or other errors while reading
		try {
			errno = 0;
			std::string temp;
			while (std::getline(filestream, temp)) {}
		} catch (std::ios_base::failure &err) {
			if (errno != 0) {
				placeFileErrorMsg(
					std::string(std::strerror(errno)), std::string(argv[1]));
				return -1;
			}
		}
		filestream.close();
		filestream.open(argv[1]);
		lexerInput << filestream.rdbuf();
		filestream.close();
		filestream.open(argv[1]);
		parserInput << filestream.rdbuf();
		filestream.close();
		check = lexerInput.str();
	} else {
		std::cout << "═════════════════════════" << std::endl;
		std::cout << "\033[1;31m" << "ERROR: " << "\033[1;33m" <<
		"Too many arguments" << "\033[0m" << std::endl;
		std::cout << "═════════════════════════" << std::endl;
		return -1;
	}

	// Checking for lexical errors

	try {
		lexer.analyze(check, lexerInput);
	}
	catch (Lexer::LexicalException &e) {
		std::cout << "\033[1;32m" <<
		"Terminating the program due to lexical errors..." << "\033[0m"
		<< std::endl;
		for (int i = 0; i < lexer.getLen(); i++) {
			std::cout << "\xe2\x95\x90";
		}
		std::cout << std::endl;
		return -1;
	}

	// Parsing the commands

	try {
		while (!(parserInput.eof()) && action != EXIT) {
			++count;
			std::getline(parserInput, line);
			if (line.empty() || line[0] == ';') {
				continue;
			}
			parser.parse(line, stdinput, count);
			action = parser.getAct();
			if ((action == POP || action == DUMP || action == ASSERT ||
				action == PRINT) && avmStack.empty()) {
				throw EmptyStackException();
			}
			if ((action == ADD || action == DIV || action == SUB ||
				action == MUL || action == MOD) && avmStack.size() < 2) {
				throw LessThen2Exception();
			}
			switch (action) {
				case PUSH: {
					IOperand const *num = fact.createOperand(
						parser.getType(), parser.getNum());
					avmStack.push_back(num);
					break;
				}
				case POP: {
					delete avmStack.back();
					avmStack.pop_back();
					break;
				}
				case DUMP: {
					for (std::list<const IOperand *>::iterator i = --avmStack.end();
						i != --avmStack.begin(); --i) {
						std::cout << (*i)->toString() << std::endl;
					}
					break;
				}
				case ASSERT: {
					if (!(avmStack.back()->getType() == parser.getType() &&
					std::stold(parser.getNum()) == std::stold(avmStack.back()->toString()))) {
						throw AssertionException();
					}
					break;
				}
				case ADD: {
					IOperand const *v1 = avmStack.front();
					avmStack.pop_front();
					IOperand const *v2 = avmStack.front();
					avmStack.pop_front();
					IOperand const *newbie = *v1 + *v2;
					avmStack.push_front(newbie);
					delete v1;
					delete v2;
					break;
				}
				case SUB: {
					IOperand const *v1 = avmStack.front();
					avmStack.pop_front();
					IOperand const *v2 = avmStack.front();
					avmStack.pop_front();
					IOperand const *newbie = *v1 - *v2;
					avmStack.push_front(newbie);
					delete v1;
					delete v2;
					break;
				}
				case MUL: {
					IOperand const *v1 = avmStack.front();
					avmStack.pop_front();
					IOperand const *v2 = avmStack.front();
					avmStack.pop_front();
					IOperand const *newbie = *v1 * *v2;
					avmStack.push_front(newbie);
					delete v1;
					delete v2;
					break;
				}
				case DIV: {
					IOperand const *v1 = avmStack.front();
					avmStack.pop_front();
					IOperand const *v2 = avmStack.front();
					avmStack.pop_front();
					IOperand const *newbie = *v1 / *v2;
					avmStack.push_front(newbie);
					delete v1;
					delete v2;
					break;
				}
				case MOD: {
					IOperand const *v1 = avmStack.front();
					avmStack.pop_front();
					IOperand const *v2 = avmStack.front();
					avmStack.pop_front();
					IOperand const *newbie = *v1 % *v2;
					avmStack.push_front(newbie);
					delete v1;
					delete v2;
					break;
				}
				case PRINT: {
					if (avmStack.back()->getType() == 0) {
						int ch = std::stoi(avmStack.back()->toString());
						if (std::isprint(ch)) {
							std::cout << static_cast<char>(ch) << std::endl;
						} else {
							throw NonInt8Exception(ch);
						}
					} else {
						throw NonPrintableException();
					}
					break;
				}
				case EXIT:
					break;
				case EMPTY:;
			}
		}
	}
	catch (std::exception &e) {
		placeFileErrorMsg(e.what(), ("Line " + std::to_string(count) + ": " + line));
	}

	return 0;
}
