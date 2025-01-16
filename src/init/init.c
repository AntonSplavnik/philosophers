/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:47:38 by asplavni          #+#    #+#             */
/*   Updated: 2025/01/16 21:25:04 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	data_init(t_data *data)
{
	data->philos_alive = 1;
	data->philos = NULL;
	data->threads = NULL;
	data->forks = NULL;
}

void	philo_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->number_of_philosophers * sizeof(t_philos));
	if(data->philos == NULL)
	{
		free_all(data);
		exit(1);
	}
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].has_eaten = 0;
		data->philos[i].is_dead = 0;
		data->philos[i].timer_start = get_time();
		data->philos[i].timer_last_meal = get_time();

		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
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
		free_all(data);
		exit (1);
	}
	if (pthread_create(&data->manager, NULL, &manager_routine, NULL) != 0)
	{
		free_all(data);
		exit (1);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, &philo_routine, NULL) != 0)
		{
			free_all(data);
			exit (1);
		}
		custom_usleep(1);
		i++;
	}
}

void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
		{
			free_all(data);
			exit (1);
		}
		i++;
	}
}

void	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->number_of_philosophers *sizeof(pthread_mutex_t));
	if (data->forks == NULL)
	{
		free_all(data);
		exit (1);
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		free_all(data);
		exit (1);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free_all(data);
			exit (1);
		}
		i++;
	}
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->print) != 0)
	{
		free_all(data);
		exit (1);
	}
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
		{
			free_all(data);
			exit (1);
		}
		i++;
	}
}
