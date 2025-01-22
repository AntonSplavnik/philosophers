/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:47:38 by asplavni          #+#    #+#             */
/*   Updated: 2025/01/22 21:55:44 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->fork_status = malloc(data->number_of_philosophers * sizeof(int));
	if (data->fork_status == NULL)
		exit (1);
	while (i < data->number_of_philosophers)
	{
		data->fork_status[i] = 0;
		i++;
	}
	data->philos_alive = 1;
	data->philos = NULL;
	data->threads = NULL;
	data->mutex_forks = NULL;
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->number_of_philosophers * sizeof(t_philo));
	if(data->philos == NULL)
	{
		free_data(data);
		exit(1);
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
}

void	threads_init(t_data *data)
{
	int	i;

	i = 0;
	data->threads = malloc(data->number_of_philosophers * sizeof(pthread_t));
	if (data->threads == NULL)
	{
		free_data(data);
		exit (1);
	}
	if (pthread_create(&data->thread_manager, NULL, &manager_routine, (void *)data) != 0)
	{
		free_data(data);
		exit (1);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, &philo_routine, (void *)&data->philos[i]) != 0)
		{
			free_data(data);
			exit (1);
		}
		i++;
	}
}

void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->thread_manager, NULL);

	while (i < data->number_of_philosophers)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_forks = malloc(data->number_of_philosophers *sizeof(pthread_mutex_t));
	if (data->mutex_forks == NULL)
	{
		free_data(data);
		exit (1);
	}
	if (pthread_mutex_init(&data->mutex_is_alive, NULL) != 0)
	{
		free_data(data);
		exit (1);
	}
	if (pthread_mutex_init(&data->mutex_last_meal, NULL) != 0)
	{
		free_data(data);
		exit (1);
	}
	if (pthread_mutex_init(&data->mutex_status, NULL) != 0)
	{
		free_data(data);
		exit (1);
	}
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
	{
		free_data(data);
		exit (1);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->mutex_forks[i], NULL) != 0)
		{
			free_data(data);
			exit (1);
		}
		custom_usleep(1);
		i++;
	}
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_is_alive);
	pthread_mutex_destroy(&data->mutex_last_meal);
	pthread_mutex_destroy(&data->mutex_status);

	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&data->mutex_forks[i]) != 0)
		{
			free_data(data);
			exit (1);
		}
		i++;
	}
}
