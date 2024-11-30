/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:03:12 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/01 00:04:25 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strcmp(char *input1, char *input2)
{
	int	i;

	i = 0;
	while (input1[i])
	{
		if (input1[i] != input2[i])
		{
			return (1);
		}
		i++;
	}
	if (input1[i] || input2[i])
		return (1);
	return (0);
}
