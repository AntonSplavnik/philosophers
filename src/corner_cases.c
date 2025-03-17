/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:29:01 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/03/16 14:45:02 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo(t_data *data)
{
	if (data->number_of_philosophers == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%d 1 died\n", data->time_to_die);
		return (1);
	}
	return (0);
}

int	zero_philo(t_data *data)
{
	if (data->number_of_philosophers == 0)
		return (1);
	return (0);
}

int	zero_cycles(t_data *data)
{
	if (data->num_of_times_each_philo_must_eat == 0)
		return (1);
	return (0);
}

int	corner_cases(t_data *data)
{
	if (one_philo(data))
		return (1);
	if (zero_philo(data))
		return (1);
	if (zero_cycles(data))
		return (1);
	return (0);
}
