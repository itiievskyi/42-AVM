/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:25:42 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/23 15:25:43 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FACTORY_H
# define FACTORY_H

# include <iostream>
# include "IOperand.hpp"
# include "Operand.tpp"

class Factory {

public:

	Factory(void);
	Factory(const Factory&);
	Factory& operator=(const Factory&);
	~Factory(void);

	IOperand const *createOperand(eOperandType type, std::string const &value) const;

	typedef const IOperand* (Factory::*Func)(std::string const &) const;

private:

	IOperand const *createInt8(std::string const &value) const;
	IOperand const *createInt16(std::string const &value) const;
	IOperand const *createInt32(std::string const &value) const;
	IOperand const *createFloat(std::string const &value) const;
	IOperand const *createDouble(std::string const &value) const;

	Func _funcs[5];

};

#endif
