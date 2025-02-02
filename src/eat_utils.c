/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:19:54 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 19:24:14 by antonsplavn      ###   ########.fr       */
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
