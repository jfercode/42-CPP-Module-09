/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:21:35 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/06 16:55:04 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN::~RPN(void) {}

RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

bool	RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');	
}

int	RPN::applyOperator(char op, int a, int b) const
{
	int	result = 0;
	if (isOperator(op))
	{
		switch (op)
		{
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = a / b;
				break;
			default:
				result = a + b;
				break;
		}
	}
	return (result);
}

void	RPN::evaluate(const std::string& expression)
{	
	std::istringstream ss(expression);
	std::string token;	
	while (ss >> token)
	{
		if (token.length() == 1 && isOperator(token[0]))
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error: invalid stack size" << std::endl;
				return;
			}
			int num02 = _stack.top(); _stack.pop();
			int num01 = _stack.top(); _stack.pop();
			if (token[0] == '/' && num02 == 0)
			{
				std::cerr << "Error: division by zero" << std::endl;
				return;
			}
			int	result = applyOperator(token[0], num01, num02);
			_stack.push(result);
		}
		else
		{
			if (token.length() != 1 && !isdigit(token[0]))
			{
				std::cerr << "Error: invalid parameter => " << token[0] << std::endl;
				return;
			}
			int value = token[0] - '0';
			_stack.push(value);
		}
	}
	if (_stack.size() != 1)
	{
		std::cerr << "Error: invalid parameters given" << std::endl;
		return;
	}
	std::cout << _stack.top() << std::endl;
}