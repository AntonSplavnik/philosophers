/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:37:16 by asplavni          #+#    #+#             */
/*   Updated: 2025/03/16 14:40:40 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * funtion for retreving current time in milliseconds.
 */
long	get_time(void)
{
	Time	time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

/**
 * elapsed time between two timestams in milliseconds.
 */
long	elapsed_time(long start, long end)
{
	return (end - start);
}

/**
 * custom usleep function with more precision.
 */
void	custom_usleep(t_data *data, long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		if (!check_philos_alive(data->philos))
			break ;
		usleep(10);
	}
}

void	print_message(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (check_philos_alive(philo))
		printf("%ld %d %s\n", \
		elapsed_time(philo->timer_start, get_time()), philo->id, message);
	pthread_mutex_unlock(&philo->data->mutex_print);
}
