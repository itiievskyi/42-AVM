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

int main(int argc, char **argv) {

	std::stack<IOperand *> avmStack;

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
		if (line != ";;") { // Checking for ctrl+D input interruption
			std::cout << "═══════════════════════════════════════════════════"
			<< std::endl << "\033[1;31m" <<
			"ERROR: The input was interrupted by pressing Ctrl+D" << std::endl
			<< "\033[1;33m" << "Use ';;' command at the start of a line instead"
			<< "\033[0m" << std::endl <<
			"═══════════════════════════════════════════════════" << std::endl;
			return -1;
		}
		check = lexerInput.str();
	} else if (argc == 2) {
		filestream.open(argv[1]);
		lexerInput << filestream.rdbuf();
		filestream.close();
		filestream.open(argv[1]);
		parserInput << filestream.rdbuf();
		filestream.close();
		check = lexerInput.str();
	} else {
		std::cout << "═════════════════════════" << std::endl;
		std::cout << "\033[1;31m" << "ERROR: Too many arguments" << "\033[0m"
		<< std::endl;
		std::cout << "═════════════════════════" << std::endl;
		return -1;
	}

	// Checking for lexical errors

	try {
		lexer.analyze(check, lexerInput);
	}
	catch (Lexer::LexicalException &e) {
		std::cout << "Terminating the program due to lexical errors..." << std::endl;
		filestream.close();
		return -1;
	}

	// Parsing the commands

	while (!(parserInput.eof()) && action != EXIT) {
		++count;
		std::cout << count << '\n';
		std::getline(parserInput, line);
		if (line.empty() || line[0] == ';') {
			continue;
		}
		parser.parse(line, stdinput, count);
		action = parser.getAct();
		switch (action) {
			case PUSH:

			case POP:

			case DUMP:

			case ASSERT:

			case ADD:

			case SUB:

			case MUL:

			case DIV:

			case MOD:

			case PRINT:

			case EXIT:
				break;
			case ERROR:
				std::cout << "Terminating the program due to error..."
				<< std::endl;
				std::system("leaks -q avm");
				return -1;
			case EMPTY:;
		}
	}

/*
	Factory *fact;
	fact = new Factory();

	IOperand const *a = fact->createOperand(Int32, argv[1]);
	IOperand const *b = fact->createOperand(Float, argv[2]);

	std::cout << a->toString() << '\n';
	std::cout << b->toString() << '\n';

	std::cout << a->getType() << '\n';
	std::cout << b->getType() << '\n';

	std::cout << " + = " << (*a + *b)->toString() << '\n';
	std::cout << " - = " << (*a - *b)->toString() << '\n';
	std::cout << " * = " << (*a * *b)->toString() << '\n';
	std::cout << " / = " << (*a / *b)->toString() << '\n';
	std::cout << " % = " << (*a % *b)->toString() << '\n';
*/

	std::system("leaks -q avm");
	return 0;
}
