/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:05:57 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/06 12:51:26 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "include/BitcoinExchange.hpp"

int	main (int argc, char **argv)
{
	(void) argv;
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (EXIT_FAILURE);
	}
	BitcoinExchange btc;

	btc.loadDatabase("data.csv");
	btc.processInputFile(argv[1]);
	return (EXIT_SUCCESS);
}