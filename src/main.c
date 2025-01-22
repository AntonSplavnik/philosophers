/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/22 23:31:31 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_data(t_data *data)
{
	free(data->fork_status);
	free(data->mutex_forks);
	free(data->philos);
	free(data->threads);
}

int	take_left_fork(t_philo *philo)
{
	int	left_fork_id;

	left_fork_id = philo->id - 1;

	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_is_alive);
		if (!philo->data->philos_alive)
		{
			pthread_mutex_unlock(&philo->data->mutex_is_alive);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_is_alive);

		pthread_mutex_lock(&philo->data->mutex_status);
		if (philo->data->fork_status[left_fork_id] == 0)
		{
			philo->data->fork_status[left_fork_id] = 1;
			pthread_mutex_unlock(&philo->data->mutex_status);
			// usleep(10);

			pthread_mutex_lock(philo->mutex_left_fork);

			pthread_mutex_lock(&philo->data->mutex_print);
			printf("%ld %d has taken a left fork\n", elapsed_time(philo->timer_start, get_time()), philo->id);
			pthread_mutex_unlock(&philo->data->mutex_print);

			return (0);
		}
		pthread_mutex_unlock(&philo->data->mutex_status);
		// usleep(100);
	}

	return (1);
}

int	take_right_fork(t_philo *philo)
{
	int	right_fork_id;

	right_fork_id = philo->id % philo->data->number_of_philosophers;

	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_is_alive);
		if (!philo->data->philos_alive)
		{
			pthread_mutex_unlock(&philo->data->mutex_is_alive);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_is_alive);

		pthread_mutex_lock(&philo->data->mutex_status);
		if (philo->data->fork_status[right_fork_id] == 0)
		{
			philo->data->fork_status[right_fork_id] = 1;
			pthread_mutex_unlock(&philo->data->mutex_status);
			// usleep(10);

			pthread_mutex_lock(philo->mutex_right_fork);

			pthread_mutex_lock(&philo->data->mutex_print);
			printf("%ld %d has taken a right fork\n", elapsed_time(philo->timer_start, get_time()), philo->id);
			pthread_mutex_unlock(&philo->data->mutex_print);

			return (0);
		}
		pthread_mutex_unlock(&philo->data->mutex_status);
		// usleep(100);
	}

/* 	pthread_mutex_lock(&philo->data->mutex_status);
	if (philo->data->fork_status[right_fork_id] == 1)
		philo->data->fork_status[right_fork_id - 1] = 0;
	pthread_mutex_unlock(&philo->data->mutex_status);
	// usleep(10);

	pthread_mutex_unlock(philo->mutex_left_fork); */

	return (1);
}

int take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ld %d is thinking\n", elapsed_time(philo->timer_start, get_time()), philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);

	if (philo->id % 2 == 0)
	{
		if (take_right_fork(philo) || take_left_fork(philo))
			return (1);
	}
	else
	{
		if (take_left_fork(philo) || take_right_fork(philo))
			return (1);
	}

	return (0);
}

/* int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ld %d is thinking\n", elapsed_time(philo->timer_start, get_time()), philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);

	if (philo->id % 2 == 0)
		usleep(500);
	while(philo->data->philos_alive)
	{
		if (take_left_fork(philo))
			return (1);
		if (take_right_fork(philo))
			return (1);
		break;
	}
	return (0);
} */

int	eat(t_philo *philo)
{
	int	left_fork_id;
	int	right_fork_id;

	left_fork_id = philo->id - 1;
	right_fork_id = philo->id % philo->data->number_of_philosophers;


	pthread_mutex_lock(&philo->data->mutex_is_alive);
	if (!philo->data->philos_alive)
	{
		pthread_mutex_unlock(&philo->data->mutex_is_alive);

		pthread_mutex_unlock(philo->mutex_left_fork);
		pthread_mutex_unlock(philo->mutex_right_fork);

		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_is_alive);

	pthread_mutex_lock(&philo->data->mutex_last_meal);
	philo->timer_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->mutex_last_meal);

	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ld %d is eating\n", elapsed_time(philo->timer_start, get_time()), philo->id);
	pthread_mutex_unlock(&philo->data->mutex_print);

	custom_usleep(philo->data->time_to_eat);

	pthread_mutex_lock(&philo->data->mutex_status);
	philo->data->fork_status[left_fork_id] = 0;
	pthread_mutex_unlock(&philo->data->mutex_status);

	pthread_mutex_unlock(philo->mutex_left_fork);

	pthread_mutex_lock(&philo->data->mutex_status);
	philo->data->fork_status[right_fork_id] = 0;
	pthread_mutex_unlock(&philo->data->mutex_status);

	pthread_mutex_unlock(philo->mutex_right_fork);

	philo->has_eaten++;

	return (0);
}

int	p_sleep(t_philo *philo)
{
	if (1)
	{
		pthread_mutex_lock(&philo->data->mutex_is_alive);
		if (!philo->data->philos_alive)
		{
			pthread_mutex_unlock(&philo->data->mutex_is_alive);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutex_is_alive);

		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %d is sleeping\n", elapsed_time(philo->timer_start, get_time()), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);

		custom_usleep(philo->data->time_to_sleep);
	}
	return (0);
}

void	*manager_routine(void *arg)
{
	t_data	*data;
	int	i;

	data = (t_data *)arg;
	i = 0;
	while(1)
	{
		if (i >= data->number_of_philosophers)
			i = 0;

		pthread_mutex_lock(&data->mutex_last_meal);
		if (get_time() - data->philos[i].timer_last_meal > data->time_to_die)
		{
			pthread_mutex_unlock(&data->mutex_last_meal);

			pthread_mutex_lock(&data->mutex_is_alive);
			data->philos_alive = 0;
			pthread_mutex_unlock(&data->mutex_is_alive);

			custom_usleep(1);
			pthread_mutex_lock(&data->mutex_print);
			printf ("%ld %d died\n",elapsed_time(data->philos[i].timer_start, get_time()), data->philos[i].id);
			pthread_mutex_unlock(&data->mutex_print);

			return (NULL);
		}
		pthread_mutex_unlock(&data->mutex_last_meal);
		i++;
		// usleep(10);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);

	while(1)
	{
		pthread_mutex_lock(&philo->data->mutex_is_alive);
		if (!philo->data->philos_alive)
		{
			pthread_mutex_unlock(&philo->data->mutex_is_alive);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_is_alive);

		if (take_forks(philo))
			break;
		if (eat(philo))
			break;
		if (p_sleep(philo))
			break;

	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	validate_arguments(argc, argv);
	parsing(&data, argc, argv);
	data_init(&data);
	mutex_init(&data);
	philo_init(&data);
	threads_init(&data);
	thread_join(&data);
	mutex_destroy(&data);
	free_data(&data);
	return (0);
}
