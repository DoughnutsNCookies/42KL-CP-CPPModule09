/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:35:37 by schuah            #+#    #+#             */
/*   Updated: 2023/04/04 19:43:44 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
		this->_stack = src._stack;
	return (*this);
}

void RPN::doRpn(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << av[0] << " [expression]" << std::endl;
		return ;
	}

	std::stringstream	ss(av[1]);
	int					error = 0;
	char				token;
	while (ss >> token && error == 0)
	{
		if (this->_stack.size() < 2)
			(token >= '0' && token <= '9') ? this->_stack.push(token) : (void)(error = 1);
		else
		{
			std::string	ops = "+-*/";
			if (ops.find(token) == std::string::npos)
				error = 1;
			else
			{
				int	b = this->_stack.top() - '0';
				this->_stack.pop();
				int	a = this->_stack.top() - '0';
				this->_stack.pop();
				if (token == '+')
					this->_stack.push(a + b + '0');
				else if (token == '-')
					this->_stack.push(a - b + '0');
				else if (token == '*')
					this->_stack.push(a * b + '0');
				else if (token == '/')
					b == 0 ? (void)(error = 1) : this->_stack.push(a / b + '0');
			}
		}
	}
	std::cout << ((error || this->_stack.size() != 1) ? "Error" : std::to_string(this->_stack.top() - '0')) << std::endl;
}
