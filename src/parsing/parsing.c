/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:52:24 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 05:28:10 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_and_assign(int *dest, char *arg)
{
	if (validate_input_string(arg) != 0 \
		|| validate_number_limits(ft_atoi(arg)) != 0)
		return (1);
	*dest = ft_atoi(arg);
	return (0);
}

int	parsing(t_data *data, int argc, char **argv)
{
	if (validate_and_assign(&data->number_of_philosophers, argv[1]) != 0)
		return (1);
	if (validate_and_assign(&data->time_to_die, argv[2]) != 0)
		return (1);
	if (validate_and_assign(&data->time_to_eat, argv[3]) != 0)
		return (1);
	if (validate_and_assign(&data->time_to_sleep, argv[4]) != 0)
		return (1);
	if (argc == 6)
	{
		if (validate_input_string(argv[5]) != 0 \
			|| validate_number_limits(ft_atoi(argv[5])) != 0)
			data->num_of_times_each_philo_must_eat = -1;
		else
			data->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	}
	else
		data->num_of_times_each_philo_must_eat = -1;
	return (0);
}
