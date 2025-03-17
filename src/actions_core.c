/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:49:31 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/03/17 12:56:52 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think(t_philo *philo)
{
	long	think1;
	long	think2;

	think1 = 0;
	think2 = 0;
	if (!check_philos_alive(philo))
		return (1);
	print_message(philo, "is thinking");
	if (philo->data->number_of_philosophers % 2)
	{
		think1 = philo->data->time_to_die - philo->data->time_to_sleep \
				- philo->data->time_to_eat;
		think2 = philo->data->time_to_eat + 10;
		if (think2 < think1)
			think1 = think2;
		usleep(think1 * 1000);
	}
	else
		usleep(200);
	return (0);
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
	custom_usleep(philo->data, philo->data->time_to_eat);
	unlock_forks(philo);
	count_meals(philo);
	return (0);
}

int	p_sleep(t_philo *philo)
{
	if (!check_philos_alive(philo))
		return (1);
	print_message(philo, "is sleeping");
	custom_usleep(philo->data, philo->data->time_to_sleep);
	return (0);
}
