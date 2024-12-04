/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:11:22 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/04 19:19:38 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	argument_checker(int argc, char **argv)
{
	int	i;

	i = 1;

	if (argc > 6)
	{
		ft_putstr("Too many arguments. 5 - 6\n");
		exit (1);
	}
	else if (argc < 5)
	{
		ft_putstr("Not enough arguments. 5 - 6\n");
		exit (1);
	}
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			ft_putstr("Error: empty argument\n");
			exit (1);
		}
		i++;
	}
}

int	input_restrictions_helper(char *input_str, int i)
{
	if (input_str[i] == ' ')
	{
		ft_putstr("Error: space\n");
		exit (1);
	}
	else if (input_str[i] < '0' || input_str[i] > '9')
	{
		ft_putstr("Error: non numeric value\n");
		exit (1);
	}
	return (0);
}

int	input_restrictions(char *input_str)
{
	int	i;

	i = 0;
	if (input_str[i] == '-')
	{
		ft_putstr("Error: negative value found\n");
		exit (1);
	}
	if (input_str[i] == '0' && \
		(input_str[i + 1] >= '0' && input_str[i + 1] <= '9'))
	{
		ft_putstr ("Error: 0 before a number\n");
		exit (1);
	}
	while (input_str[i])
	{
		if (input_restrictions_helper(input_str, i) == 1)
			exit (1);
		i++;
	}
	return (0);
}

int	limits(long number)
{
	if (number > INT_MAX || number < INT_MIN)
	{
		ft_putstr("Error: limits\n");
		exit (1);
	}
	return (0);
}
