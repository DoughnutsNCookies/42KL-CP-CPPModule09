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

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << av[0] << " [expression]" << std::endl;
		return (1);
	}

	std::stack<char> stack;
	std::stringstream ss(av[1]);
	int error = 0;
	char token;
	while (ss >> token && error == 0)
	{
		if (stack.size() < 2)
			(token >= '0' && token <= '9') ? stack.push(token) : (void)(error = 1);
		else
		{
			std::string ops = "+-*/";
			if (ops.find(token) == std::string::npos)
				error = 1;
			else
			{
				int b = stack.top() - '0';
				stack.pop();
				int a = stack.top() - '0';
				stack.pop();
				if (token == '+')
					stack.push(a + b + '0');
				else if (token == '-')
					stack.push(a - b + '0');
				else if (token == '*')
					stack.push(a * b + '0');
				else if (token == '/')
					b == 0 ? (void)(error = 1) : stack.push(a / b + '0');
			}
		}
	}
	std::cout << ((error || stack.size() != 1) ? "Error" : std::to_string(stack.top() - '0')) << std::endl;
	return (0);
}
