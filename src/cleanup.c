/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:53:32 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 05:25:35 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	free(data->mutex_forks);
	free(data->philos);
	free(data->threads);
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

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_is_alive);
	pthread_mutex_destroy(&data->mutex_last_meal);
	pthread_mutex_destroy(&data->mutex_has_eaten);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
}
