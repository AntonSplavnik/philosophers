/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:11:22 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 05:28:36 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
	{
		ft_putstr("Not enough arguments. Should be (4 - 5) arguments\n");
		return (1);
	}
	else if (argc > 6)
	{
		ft_putstr("Too many arguments. should be (4 - 5) arguments\n");
		return (1);
	}
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			ft_putstr("Error: empty argument found\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_characters(char *input_str, int i)
{
	if (input_str[i] == ' ')
	{
		ft_putstr("Error: space found\n");
		return (1);
	}
	else if (input_str[i] < '0' || input_str[i] > '9')
	{
		ft_putstr("Error: non numeric value found\n");
		return (1);
	}
	return (0);
}

int	validate_input_string(char *input_str)
{
	int	i;

	i = 0;
	if (input_str[i] == '-')
	{
		ft_putstr("Error: negative value found\n");
		return (1);
	}
	if (input_str[i] == '0' && \
		(input_str[i + 1] >= '0' && input_str[i + 1] <= '9'))
	{
		ft_putstr ("Error: 0 before a number found\n");
		return (1);
	}
	while (input_str[i])
	{
		if (validate_characters(input_str, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	validate_number_limits(long number)
{
	if (number > INT_MAX || number < INT_MIN)
	{
		ft_putstr("Error: limits exceeded\n");
		return (1);
	}
	return (0);
}
