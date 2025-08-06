/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:20:52 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/06 13:08:48 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this->_database != other._database)
		this->_database = other._database;
	return (*this);
}

static bool isLeap(int year)
{
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool	BitcoinExchange::isValidDate(const std::string &date) const
{
	int	y, m, d;
	int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31 };
	
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);	
	
	std::stringstream year(date.substr(0, 4).c_str());
	year >> y;
	std::stringstream month(date.substr(5, 2).c_str());
	month >> m;
	std::stringstream day(date.substr(8, 2).c_str());
	day >> d;
	if (year.fail() || month.fail() || day.fail())
		return (std::cerr << "Error: invalid conversion on date => " << date << std::endl, false);

	if (m < 1 || m > 12)
        return (std::cerr << "Error: invalid month on date => " << date << std::endl, false);
	if (isLeap(y))
		days_in_month[2] = 29;
	if (d < 1 || d > days_in_month[m])
		return(std::cerr << "Error; invalid day on date => " << date << std::endl, false);
	return (true);
}

bool	BitcoinExchange::isValidValue(const std::string &valueStr, float& value) const
{	
	std::stringstream valueS(valueStr);
	valueS >> value;
	if (valueS.fail())
		return (std::cerr << "Error: invalid conversion on value => " << valueStr << std::endl, false);
	
	if (value < 0 || value > 1000)
		return (false);
	return (true);
}

std::string BitcoinExchange::trim(const std::string& str) const 
{
	size_t start = str.find_first_not_of(" \t");
	size_t end = str.find_last_not_of(" \t");

	if (start == std::string::npos || end == std::string::npos)
		return ("");

	return (str.substr(start, end - start + 1));
}

void	BitcoinExchange::loadDatabase(const std::string& filename)
{
	float value = 0;
	std::string line;
	std::ifstream file(filename.c_str());
	
	/*	File availability test	*/
	if (!file)
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}

	/*	File loading data into _database	*/
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::istringstream lineSs(line);
		std::string date, valueStr;
		if (std::getline(lineSs, date, ',') && std::getline(lineSs, valueStr))
		{
			value = atof(valueStr.c_str());
			_database[date] = value;	
		}
	}
	file.close();
}

void	BitcoinExchange::processInputFile(const std::string& filename)
{
	float value;
	std::string line;
	std::ifstream file(filename.c_str());
	
	/*	File availability test*/
	if (!file)
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return;
	}
	
	/*	File reading	*/
	std::getline(file, line);
	while (std::getline(file, line))
	{
		/*	Input file check	*/
		std::istringstream lineSs(line);
		std::string date, valueStr;
		if (!std::getline(lineSs, date, '|') || !std::getline(lineSs, valueStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;	
		}
		/*	Prepare date and valueStr	*/
		date = trim(date);
		valueStr = trim(valueStr);
		
		/*	Date format and value check	*/
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input date => " << line << std::endl;
			continue;	
		}
		if (!isValidValue(valueStr, value))
		{
			if (value < 0)
				std::cerr << "Error: not a positive number => " << value << std::endl; 
			else
				std::cerr << "Error: too large a number => " << value << std::endl;
			continue;
		}

		/*	Map iteration */
		std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
		if (it == _database.end() || it->first != date)
		{
			if (it != _database.begin())
				--it;
			else
			{
				std::cerr << "Error: no earlier date available." << std::endl;
				continue;
			}
		}

		/*	Output declaration [date => value = result]	*/
		float result = value * it->second;
		std::cout << date << " => " << value << " = " << result << std::endl; 
	}
	file.close();
}
