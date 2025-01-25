/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:21:00 by asplavni          #+#    #+#             */
/*   Updated: 2025/01/25 05:05:47 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*manager_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (i >= data->number_of_philosophers)
			i = 0;
		if (philo_death_status(data, i))
			break ;
		if (data->num_of_times_each_philo_must_eat > 0 && \
										philo_food_count_status(data))
			break ;
		i++;
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (!check_philos_alive(philo))
			break ;
		if (take_forks(philo))
			break ;
		if (eat(philo))
			break ;
		if (p_sleep(philo))
			break ;
	}
	return (NULL);
}
