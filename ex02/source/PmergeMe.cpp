/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:14:07 by jaferna2          #+#    #+#             */
/*   Updated: 2025/08/13 10:59:05 by jaferna2         ###   ########.fr       */
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
			throw std::runtime_error("Error: invalid parameter");
		int value = atoi(args[i].c_str());
		if (value < 0)
			throw std::runtime_error("Error: value < 0");
		_vec.push_back(value);
		_deq.push_back(value);
	}
	
}

// MATHS => J(0)=0, J(1)=1, J(n)=J(n−1)+2×J(n−2) for n≥2
static std::vector<size_t> generateJacobshalSequence(size_t n)
{
	std::vector <size_t> seq;
	
	if (n == 0)
		return seq;
	
	//	Generate the jacobsthal numbers until jacob number < n
	std::vector <size_t> jacob;
	jacob.push_back(0);
	jacob.push_back(1);
	while (jacob.back() < n)
		jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);
	
	//	Generate inserion order indexes
	std::vector<bool> inserted(n, false);
    for (size_t k = 1; k < jacob.size(); ++k) 
	{
        size_t start = jacob[k];
        if (start > n)
            start = n;
        size_t end = (k + 1 < jacob.size()) ? jacob[k + 1] : n;
        if (end > n)
            end = n;
        size_t i = start;
        while (i > jacob[k - 1]) 
		{
            if (i <= n && !inserted[i - 1]) 
			{
                seq.push_back(i - 1);
                inserted[i - 1] = true;
            }
            --i;
        }
    }
	return (seq);
}

void	PmergeMe::mergeInsertionSortV(std::vector<int>& container)
{
	std::vector<int> mainChain;
	std::vector<int> pending;
	
	/*	1. Division into pairs and separation between major and minor	*/
	if (container.size() <= 1)
		return;
	
	for (size_t i = 0; i + 1 < container.size(); i += 2)
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
	mergeInsertionSortV(mainChain);
	
	/*	3. Insert the earrings in the correct order	using Jacobsthal */
	std::vector<size_t> jacob = generateJacobshalSequence(pending.size());
	for (size_t idx = 0; idx < jacob.size(); ++idx) 
	{
        size_t pIndex = jacob[idx];
        int value = pending[pIndex];
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
        mainChain.insert(pos, value);
    }
    container.assign(mainChain.begin(), mainChain.end());
}

void	PmergeMe::mergeInsertionSortD(std::deque<int>& container)
{
	std::deque<int> mainChain;
	std::deque<int> pending;
	
	/*	1. Division into pairs and separation between major and minor	*/
	if (container.size() <= 1)
		return;
	
	for (size_t i = 0; i + 1 < container.size(); i += 2)
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
	mergeInsertionSortD(mainChain);
	
	/*	3. Insert the earrings in the correct order	using Jacobsthal sequence */
	std::vector<size_t> jacob = generateJacobshalSequence(pending.size());
	for (size_t idx = 0; idx < jacob.size(); ++idx)
	{
        size_t pIndex = jacob[idx];
        int value = pending[pIndex];
        std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), value);
        mainChain.insert(pos, value);
    }
    container.assign(mainChain.begin(), mainChain.end());
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
	printContainer("Before_vec: ", _vec);
	printContainer("Before_deq: ", _deq);
	

	/*	Vec Insertion sort	*/
	clock_t	startVec = clock();
	mergeInsertionSortV(_vec);
	clock_t endVec = clock();

	std::cout << "/*****************/" << std::endl;

	/*	Deque Insertion sort	*/
	clock_t	startDeq = clock();
	mergeInsertionSortD(_deq);
	clock_t endDeq = clock();

	/*	Print solved state	*/
	printContainer("After_vec: ", _vec);
	printContainer("After_deq: ", _deq);

	
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