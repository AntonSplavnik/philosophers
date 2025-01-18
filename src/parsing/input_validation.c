/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:11:22 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/18 20:35:28 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 1;

	if (argc > 6)
	{
		ft_putstr("Too many arguments. should be (4 - 4) arguments\n");
		exit (1);
	}
	else if (argc < 5)
	{
		ft_putstr("Not enough arguments. Should be (4 - 5) arguments\n");
		exit (1);
	}
	while (argv[i])
	{
		if (argv[i][0] == '\0')
		{
			ft_putstr("Error: empty argument found\n");
			exit (1);
		}
		i++;
	}
}

int	validate_characters(char *input_str, int i)
{
	if (input_str[i] == ' ')
	{
		ft_putstr("Error: space found\n");
		exit (1);
	}
	else if (input_str[i] < '0' || input_str[i] > '9')
	{
		ft_putstr("Error: non numeric value found\n");
		exit (1);
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
		exit (1);
	}
	if (input_str[i] == '0' && \
		(input_str[i + 1] >= '0' && input_str[i + 1] <= '9'))
	{
		ft_putstr ("Error: 0 before a number found\n");
		exit (1);
	}
	while (input_str[i])
	{
		if (validate_characters(input_str, i) == 1)
			exit (1);
		i++;
	}
	return (0);
}

int	validate_number_limits(long number)
{
	if (number > INT_MAX || number < INT_MIN)
	{
		ft_putstr("Error: limits exceeded\n");
		exit (1);
	}
	return (0);
}
