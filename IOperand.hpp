/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:38:24 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/23 10:38:25 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_H
# define IOPERAND_H

# include <iostream>

enum eOperandType {
	Int8 = 0,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand {

public:

	virtual int getPrecision( void ) const = 0;
	virtual eOperandType getType( void ) const = 0;

	virtual IOperand const *operator+(IOperand const &rhs) const = 0;
	virtual IOperand const *operator-(IOperand const &rhs) const = 0;
	virtual IOperand const *operator*(IOperand const &rhs) const = 0;
	virtual IOperand const *operator/(IOperand const &rhs) const = 0;
	virtual IOperand const *operator%(IOperand const &rhs) const = 0;

	virtual std::string const & toString( void ) const = 0;
	virtual ~IOperand( void ) {}

};

#endif
