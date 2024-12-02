/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:35:02 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/02 15:06:26 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_bzero(void *str, size_t number)
{
	size_t	i;

	i = 0;
	while (i < number)
	{
		((char *)str)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*new_allocation;

	new_allocation = malloc(num * size);
	if (new_allocation == NULL)
		return (NULL);
	ft_bzero(new_allocation, num * size);
	return (new_allocation);
}

int	ft_atoi(char *input_str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	if (input_str[i] == '-' && i == 0)
	{
		sign *= -1;
		i++;
	}
	while (input_str[i])
	{
		result = result * 10 + (input_str[i] - '0');
		i++;
	}
	return ((result * sign));
}
