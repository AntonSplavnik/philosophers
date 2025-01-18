/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:52:24 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/18 20:00:57 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parsing(t_data *data, int argc, char **argv)
{
	if (validate_input_string(argv[1]) == 0 \
		&& validate_number_limits(ft_atoi(argv[1])) == 0)
		data->number_of_philosophers = ft_atoi(argv[1]);
	if (validate_input_string(argv[2]) == 0 \
	&& validate_number_limits(ft_atoi(argv[2])) == 0)
		data->time_to_die = ft_atoi(argv[2]);
	if (validate_input_string(argv[3]) == 0 \
	&& validate_number_limits(ft_atoi(argv[3])) == 0)
		data->time_to_eat = ft_atoi(argv[3]);
	if (validate_input_string(argv[4]) == 0 \
	&& validate_number_limits(ft_atoi(argv[4])) == 0)
		data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (validate_input_string(argv[5]) == 0 \
		&& validate_number_limits(ft_atoi(argv[5])) == 0)
			data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
}
