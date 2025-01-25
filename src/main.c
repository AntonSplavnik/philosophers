/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 01:36:15 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_data(t_data *data)
{
	free(data->mutex_forks);
	free(data->philos);
	free(data->threads);
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

void	print_message(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%ld %d %s\n", \
		elapsed_time(philo->timer_start, get_time()), philo->id, message);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

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
void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutex_left_fork);
	pthread_mutex_unlock(philo->mutex_right_fork);
}
void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_has_eaten);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_has_eaten);
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

int	philo_death_status(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_last_meal);
	if (get_time() - data->philos[i].timer_last_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&data->mutex_last_meal);
		pthread_mutex_lock(&data->mutex_is_alive);
		data->philos_alive = 0;
		pthread_mutex_unlock(&data->mutex_is_alive);
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

void	*manager_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		if (i >= data->number_of_philosophers)
			i = 0;
		if (philo_death_status(data, i))
			break ;
		if (data->num_of_times_each_philo_must_eat > 0 && \
										philo_food_count_status(data))
			break ;
		i++;
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (!check_philos_alive(philo))
			break ;
		if (take_forks(philo))
			break ;
		if (eat(philo))
			break ;
		if (p_sleep(philo))
			break ;
	}
	return (NULL);
}

int	one_philo(t_data *data)
{
	if (data->number_of_philosophers == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		usleep(data->time_to_die * 1000);
		printf("%d 1 died\n", data->time_to_die);
		return (1);
	}
	return (0);
}

int	zero_cycles(t_data *data)
{
	if (data->num_of_times_each_philo_must_eat == 0)
		return (1);
	return (0);
}

int	corner_cases(t_data *data)
{
	if (one_philo(data))
		return (1);
	if (zero_cycles(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_arguments(argc, argv))
		return (1);
	if (parsing(&data, argc, argv))
		return (1);
	if (corner_cases(&data))
		return (0);
	data_init(&data);
	mutex_init(&data);
	philo_init(&data);
	threads_init(&data);
	thread_join(&data);
	mutex_destroy(&data);
	free_data(&data);
	return (0);
}
