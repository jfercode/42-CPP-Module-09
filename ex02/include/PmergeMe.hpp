/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:29:41 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/07 11:27:34 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

class PmergeMe
{
	private:
		std::deque<int>		_deq;
		std::vector<int>	_vec;
		
		bool isValidNumber(const std::string& str);
		void fillContainers(std::vector<std::string>& args);
		void mergeInsertionSort(std::vector<int>& container);
		void mergeInsertionSort(std::deque<int>& container);

		template <typename T>
		void insertionMergeSort(T& container);

		template <typename T>
		void printContainer(const std::string label, const T& container);

	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		~PmergeMe(void);

		PmergeMe& operator=(const PmergeMe& other);

		void run(std::vector<std::string>& args);
};

#endif