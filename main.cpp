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

#include "Operand.tpp"
#include "Factory.hpp"
#include "AbstractVM.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

int main(int argc, char **argv) {

	if (argc < 2 && argv) {return -1;}

	Factory *fact;
	fact = new Factory();

	IOperand const *a = fact->createOperand(Int32, argv[1]);
	IOperand const *b = fact->createOperand(Float, argv[2]);

	std::cout << a->toString() << '\n';
	std::cout << b->toString() << '\n';

	std::cout << a->getType() << '\n';
	std::cout << b->getType() << '\n';

	std::cout << "float min = " << -FLT_MAX << '\n';
	std::cout << "double min = " << std::numeric_limits<double>::min() << '\n';

	std::cout << " + = " << (*a + *b)->toString() << '\n';
	std::cout << " - = " << (*a - *b)->toString() << '\n';
	std::cout << " * = " << (*a * *b)->toString() << '\n';
	std::cout << " / = " << (*a / *b)->toString() << '\n';
	std::cout << " % = " << (*a % *b)->toString() << '\n';

	return 0;
}
