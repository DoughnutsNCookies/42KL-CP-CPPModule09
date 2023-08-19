/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:15:45 by schuah            #+#    #+#             */
/*   Updated: 2023/08/17 18:22:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int printAndReturn(int status, int result = 0)
{
	if (status == 0)
		std::cout << result << std::endl;
	else
		std::cout << "Error" << std::endl;
	return status;
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (printAndReturn(1));

	std::stack<int>		stack;
	std::istringstream	iss(av[1]);
	std::string			ops = "+-*/";
	std::string			token;
	while (iss >> token)
	{
		try {
			if (ops.find(token) != std::string::npos)
			{
				if (stack.size() < 2)
					throw std::exception();
				int b = stack.top();
				stack.pop();
				int a = stack.top();
				stack.pop();
				if (token == "+")
					stack.push(a + b);
				else if (token == "-")
					stack.push(a - b);
				else if (token == "*")
					stack.push(a * b);
				else if (token == "/")
					stack.push(a / b);
			} else {
				if (token[0] < '0' || token[0] > '9' || token[1] != '\0')
					throw std::exception();
				stack.push(token[0] - 48);
			}
		} catch (std::exception &e) {
			return (printAndReturn(1));
		}
	}
	return (printAndReturn(stack.size() != 1, stack.top()));
}
