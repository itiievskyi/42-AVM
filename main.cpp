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
	std::ostringstream input;

	Factory fact = Factory();
	Parser parser = Parser();
	Lexer lexer = Lexer();

	if (argc == 2) {
		filestream.open(argv[1]);
		input << filestream.rdbuf();
		filestream.close();

		std::string check = input.str();
		try {
			lexer.analyze(check, argv[1]);
		}
		catch (Lexer::LexicalException &e) {
			std::cout << "Terminating the program due to lexical errors..." << std::endl;
			filestream.close();
			return -1;
		}

		filestream.open(argv[1]);
	}

/*
	if (std::regex_search((input.rdbuf()), std::regex("exit(( )?(;)+(.)*)?"))) {
		std::cout << "SUCCESS" << '\n';
	} else {
		std::cout << "FAIL!" << '\n';
	}
*/
	while (!(filestream.eof()) && action != EXIT) {
		++count;
		std::getline (filestream, line);
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
