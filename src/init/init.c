/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:47:38 by asplavni          #+#    #+#             */
/*   Updated: 2025/01/25 05:27:33 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(t_data *data)
{
	data->philos_alive = 1;
	data->philos = NULL;
	data->threads = NULL;
	data->mutex_forks = NULL;
}

int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->number_of_philosophers * sizeof(t_philo));
	if (data->philos == NULL)
	{
		mutex_destroy(data);
		free(data->mutex_forks);
		return (1);
	}
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].has_eaten = 0;
		data->philos[i].timer_start = get_time();
		data->philos[i].timer_last_meal = get_time();
		data->philos[i].data = data;
		data->philos[i].mutex_left_fork = &data->mutex_forks[i];
		data->philos[i].mutex_right_fork = &data->mutex_forks[(i + 1) \
											% data->number_of_philosophers];
		i++;
	}
	return (0);
}

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_forks = \
				malloc (data->number_of_philosophers * sizeof(pthread_mutex_t));
	if (data->mutex_forks == NULL)
	{
		return (1);
	}
	pthread_mutex_init(&data->mutex_has_eaten, NULL);
	pthread_mutex_init(&data->mutex_is_alive, NULL);
	pthread_mutex_init(&data->mutex_last_meal, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->mutex_forks[i], NULL);
		usleep(100);
		i++;
	}
	return (0);
}

int	threads_init(t_data *data)
{
	int	i;

	i = 0;
	data->threads = malloc(data->number_of_philosophers * sizeof(pthread_t));
	if (data->threads == NULL)
	{
		mutex_destroy(data);
		free(data->mutex_forks);
		free(data->philos);
		return (1);
	}
	pthread_create(&data->thread_manager, NULL, &manager_routine, (void *)data);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->threads[i], NULL, \
						&philo_routine, (void *)&data->philos[i]);
		i++;
	}
	return (0);
}
