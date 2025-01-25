/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:49:31 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 05:24:05 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_has_eaten);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_has_eaten);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
}

void	set_timer_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_last_meal);
	philo->timer_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->mutex_last_meal);
}

int	eat(t_philo *philo)
{
	if (!check_philos_alive(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	set_timer_last_meal(philo);
	print_message(philo, "is eating");
	custom_usleep(philo->data->time_to_eat);
	unlock_forks(philo);
	count_meals(philo);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	if (!check_philos_alive(philo))
		return (1);
	print_message(philo, "is sleeping");
	custom_usleep(philo->data->time_to_sleep);
	return (0);
}
