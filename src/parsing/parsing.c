/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:52:24 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 00:19:31 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(t_data *data, int argc, char **argv)
{
	if (validate_input_string(argv[1]) != 0 \
		&& validate_number_limits(ft_atoi(argv[1])) != 0)
		return (1);
	data->number_of_philosophers = ft_atoi(argv[1] );

	if (validate_input_string(argv[2]) \
		&& validate_number_limits(ft_atoi(argv[2])) != 0)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);

	if (validate_input_string(argv[3]) != 0 \
		&& validate_number_limits(ft_atoi(argv[3])) != 0)
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);

	if (validate_input_string(argv[4]) != 0 \
		&& validate_number_limits(ft_atoi(argv[4])) != 0)
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);

	if (argc == 6)
	{
		if (validate_input_string(argv[5]) != 0 \
			&& validate_number_limits(ft_atoi(argv[5])) != 0)
			data->num_of_times_each_philo_must_eat = -1;
		else
			data->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	}
	else
		data->num_of_times_each_philo_must_eat = -1;
	return (0);
}
