/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:14:11 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/06 13:10:23 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <stdlib.h>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _database;

		bool	isValidDate(const std::string &date) const;
		bool	isValidValue(const std::string &valueStr, float& value) const;
		
		std::string	trim(const std::string& str) const;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange(void);

		BitcoinExchange& operator=(const BitcoinExchange& other);
		
		void loadDatabase(const std::string& filename);
		void processInputFile(const std::string& filename);
};

#endif
