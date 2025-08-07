/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:15:51 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/06 17:07:19 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
	private:
		std::stack<int> _stack;

		bool isOperator(char c) const;
		int applyOperator(char op, int a, int b) const;
		
	public:
		RPN(void);
		RPN(const RPN& other);
		~RPN(void);

		RPN& operator=(const RPN& other);
		
		void evaluate(const std::string& expression);
};

#endif