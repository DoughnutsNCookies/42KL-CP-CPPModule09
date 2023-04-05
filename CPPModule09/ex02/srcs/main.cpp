/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:09:42 by schuah            #+#    #+#             */
/*   Updated: 2023/04/05 17:30:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <deque>

template <class Container>
static void	insertionSort(Container &vec)
{
	for (size_t i = 1; i < vec.size(); i++)
	{
		int	tmp = vec[i];
		size_t	j = i + 1;
		while (--j > 0 && vec[j - 1] > tmp)
			vec[j] = vec[j - 1];
		vec[j] = tmp;
	}
}

template <template <typename, typename> class Container>
static std::chrono::microseconds	mergeInsertionSort(Container<int, std::allocator<int> > &vec)
{
	std::chrono::steady_clock::time_point						begin = std::chrono::steady_clock::now();
	typedef Container<int, std::allocator<int> >				ThisContainer;
	Container<ThisContainer, std::allocator<ThisContainer> >	big;

	for (size_t i = 0; i < vec.size(); i++)
		big.push_back(ThisContainer(1, vec[i]));
	while (big.size() > 1)
	{
		ThisContainer	newVec(big[0].begin(), big[0].end());
		newVec.insert(newVec.end(), big[1].begin(), big[1].end());
		big.erase(big.begin(), big.begin() + 2);
		insertionSort(newVec);
		big.push_back(newVec);
	}
	vec = big[0];
	std::chrono::steady_clock::time_point						end = std::chrono::steady_clock::now();
	return (std::chrono::duration_cast<std::chrono::microseconds>(end - begin));
}

static int	printExit(std::string str)
{
	std::cout << str << std::endl;
	return (EXIT_FAILURE);
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (printExit(std::string(av[0]) + " [int] [int] [int] ..."));

	std::vector<int>	vec;
	for (int i = 1; i < ac; i++)
	{
		if (std::all_of(av[i], av[i] + std::strlen(av[i]), &::isdigit) == false || atoi(av[i]) < 0)
			return (printExit("Error"));
		vec.push_back(atoi(av[i]));
	}
	std::deque<int>	deq(vec.begin(), vec.end());

	std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::chrono::microseconds vectorUs = mergeInsertionSort(vec);
	std::chrono::microseconds dequeUs = mergeInsertionSort(deq);
	std::cout << "\nAfter:  ";
	for (size_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
	std::cout << "Time to process a range of " << vec.size() << " elements with mergeInsertionSort: " << vectorUs.count() << " microseconds" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with mergeInsertionSort: " << dequeUs.count() << " microseconds" << std::endl;
    return (EXIT_SUCCESS);
}
