/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:38:00 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 04:57:38 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_left_fork(t_philo *philo)
{
	while (1)
	{
		if (!check_philos_alive(philo))
			break ;
		pthread_mutex_lock(philo->mutex_left_fork);
		if (check_philos_alive(philo))
			print_message(philo, "has taken a fork");
		return (0);
	}
	return (1);
}

int	take_right_fork(t_philo *philo)
{
	while (1)
	{
		if (!check_philos_alive(philo))
			break ;
		pthread_mutex_lock(philo->mutex_right_fork);
		if (check_philos_alive(philo))
			print_message(philo, "has taken a fork");
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (!check_philos_alive(philo))
		return (1);
	print_message(philo, "is thinking");
	usleep(200);
	if (philo->id % 2 == 0)
	{
		if (take_right_fork(philo))
			return (1);
		if (take_left_fork(philo))
		{
			pthread_mutex_unlock(philo->mutex_right_fork);
			return (1);
		}
	}
	else
	{
		if (take_left_fork(philo))
			return (1);
		if (take_right_fork(philo))
		{
			pthread_mutex_unlock(philo->mutex_left_fork);
			return (1);
		}
	}
	return (0);
}
