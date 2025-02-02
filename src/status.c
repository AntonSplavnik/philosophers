/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:58:15 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/02/05 17:55:24 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_death_status(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_last_meal);
	if (get_time() - data->philos[i].timer_last_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->mutex_last_meal);
		pthread_mutex_lock(&data->mutex_is_alive);
		data->philos_alive = 0;
		pthread_mutex_unlock(&data->mutex_is_alive);
		usleep(200);
		print_message(&data->philos[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_last_meal);
	return (0);
}

int	philo_food_count_status(t_data *data)
{
	int	i;
	int	finished_meal_cycels;

	i = 0;
	finished_meal_cycels = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->mutex_has_eaten);
		if (data->philos[i].has_eaten >= data->num_of_times_each_philo_must_eat)
			finished_meal_cycels++;
		i++;
		pthread_mutex_unlock(&data->mutex_has_eaten);
	}
	if (finished_meal_cycels == data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->mutex_is_alive);
		data->philos_alive = 0;
		pthread_mutex_unlock(&data->mutex_is_alive);
		return (1);
	}
	return (0);
}

int	check_philos_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_is_alive);
	if (!philo->data->philos_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_is_alive);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_is_alive);
	return (1);
}
