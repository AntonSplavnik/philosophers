/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:11:22 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/11/30 22:54:26 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	empty_argument_checker(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			ft_putstr("Error\n");
			exit (1);
		}
		i++;
	}
}

int	input_restrictions_helper(char *input_str, int i)
{
	if (input_str[i] == ' ')
	{
		ft_putstr("Error\n");
		return (1);
	}
	else if (input_str[i] < '0' || input_str[i] > '9')
	{
		ft_putstr("Error\n");
		return (1);
	}
	return (0);
}

int	input_restrictions(char *input_str)
{
	int	i;

	i = 0;
	if (input_str[i] == '-')
		i++;
	if (input_str[i] == '0' && \
		(input_str[i + 1] >= '0' && input_str[i + 1] <= '9'))
	{
		ft_putstr ("Error\n");
		return (1);
	}
	while (input_str[i])
	{
		if (input_restrictions_helper(input_str, i) == 1)
			return (1);
		i++;
	}
	if (input_str[0] == '-' && i == 1)
	{
		ft_putstr("Error\n");
		return (1);
	}
	return (0);
}

int	limits(long number)
{
	if (number > INT_MAX || number < INT_MIN)
	{
		ft_putstr("Error\n");
		return (1);
	}
	return (0);
}
