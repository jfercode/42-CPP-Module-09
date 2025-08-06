/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:02:25 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/06 16:53:27 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "include/RPN.hpp"

int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Invalid argument!" << std::endl;
		return (EXIT_FAILURE);
	}

	RPN rpn;
	rpn.evaluate(argv[1]);
	return (EXIT_SUCCESS);
}