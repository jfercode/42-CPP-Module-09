/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:14:07 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/07 12:54:05 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(const PmergeMe& other) : _deq(other._deq), _vec(other._vec) {}

PmergeMe::~PmergeMe(void) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
		this->_deq = other._deq;
	}
	return (*this);
}

bool	PmergeMe::isValidNumber(const std::string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	return (!str.empty());
}

void	PmergeMe::fillContainers(std::vector<std::string>& args)
{
	for (size_t i = 0; i < args.size(); ++i)
	{
		if (!isValidNumber(args[i]))
			throw std::runtime_error("Error");
		int value = atoi(args[i].c_str());
		if (value < 0)
			throw std::runtime_error("Error");
		_vec.push_back(value);
		_deq.push_back(value);
	}
	
}

void	PmergeMe::mergeInsertionSort(std::vector<int>& container)
{
	insertionMergeSort(container);
}

void	PmergeMe::mergeInsertionSort(std::deque<int>& container)
{
	insertionMergeSort(container);
}

template <typename T>
void	PmergeMe::insertionMergeSort(T& container)
{
	T mainChain;
	std::vector<int> pending;

	/*	1. Division into pairs and separation between major and minor	*/
	if (container.size() <= 1)
		return;

	for (size_t i = 0; i + 1 < container.size(); i+=2)
	{
		int a = container[i];
		int b = container[i + 1];
		if (a > b)
			std::swap(a, b);
		mainChain.push_back(b); // The main chain will store the highest value ones
		pending.push_back(a);	// consequently the slope will store the lowest value ones
	}
	if (container.size() % 2 == 1)
		pending.push_back(container.back());
	
	/*	2. Recursively sort the main string	*/
	insertionMergeSort(mainChain);

	/*	3. Insert the earrings in the correct order	*/
	for (size_t i = 0; i < pending.size(); ++i)
	{
		int value = pending[i];
		typename T::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
		mainChain.insert(pos, value);
	}
	container = mainChain;
}

template <typename T>
void	PmergeMe::printContainer(const std::string label, const T& container)
{
	std::cout << label;
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void	PmergeMe::run(std::vector<std::string>& args)
{
	/*	Fill containers with arguments	*/
	fillContainers(args);
	
	/*	Print the current state	*/
	printContainer("Before: ", _vec);
	
	/*	Vec Insertion sort	*/
	clock_t	startVec = clock();
	mergeInsertionSort(_vec);
	clock_t endVec = clock();

	/*	Deque Insertion sort	*/
	clock_t	startDeq = clock();
	mergeInsertionSort(_deq);
	clock_t endDeq = clock();

	/*	Print solved state	*/
	printContainer("After: ", _vec);
	
	/*	Time in secs of the operation	*/
	double vecTime = double(endVec - startVec) / CLOCKS_PER_SEC;
	double deqTime = double(endDeq - startDeq) / CLOCKS_PER_SEC;
	
	/*	Print results	*/
	std::cout << std::fixed << std::setprecision(6);
	
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector => " << vecTime << " s." << std::endl;
	
  	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque => " << deqTime << " s." << std::endl;
}