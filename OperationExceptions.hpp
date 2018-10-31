/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperationExceptions.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:12:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/10/31 16:12:57 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONEXCEPTIONS_H
# define OPERATIONEXCEPTIONS_H

# include <iostream>

class EmptyStackException : public std::exception {

	public:
		EmptyStackException(void);
		EmptyStackException(const EmptyStackException &src);
		virtual ~EmptyStackException(void) throw();
		EmptyStackException &operator=(const EmptyStackException &src);
		virtual const char *what() const throw();
};

class NonPrintableException : public std::exception {

	public:
		NonPrintableException(void);
		NonPrintableException(const NonPrintableException &src);
		virtual ~NonPrintableException(void) throw();
		NonPrintableException &operator=(const NonPrintableException &src);
		virtual const char *what() const throw();
};

class NonInt8Exception : public std::exception {

	public:
		NonInt8Exception(void);
		NonInt8Exception(int line);
		NonInt8Exception(const NonInt8Exception &src);
		virtual ~NonInt8Exception(void) throw();
		NonInt8Exception &operator=(const NonInt8Exception &src);
		virtual const char *what() const throw();

	private:
		int _line;
};

class AssertionException : public std::exception {

	public:
		AssertionException(void);
		AssertionException(const AssertionException &src);
		virtual ~AssertionException(void) throw();
		AssertionException &operator=(const AssertionException &src);
		virtual const char *what() const throw();
};

class LessThen2Exception : public std::exception {

	public:
		LessThen2Exception(void);
		LessThen2Exception(const LessThen2Exception &src);
		virtual ~LessThen2Exception(void) throw();
		LessThen2Exception &operator=(const LessThen2Exception &src);
		virtual const char *what() const throw();
};

#endif
