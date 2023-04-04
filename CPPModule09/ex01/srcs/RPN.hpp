/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:28:52 by schuah            #+#    #+#             */
/*   Updated: 2023/04/04 19:42:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>

class	RPN
{
	public:
		/* Orthrodox canonical form */
		RPN();
		~RPN();
		RPN(const RPN &src);
		RPN	&operator=(const RPN &src);

		/* Member function */
		void	doRpn(int ac, char **av);

	private:
		std::stack<char>	_stack;
};

#endif
