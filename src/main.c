/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/17 23:01:48 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_all(t_data *data)
{
	free(data->fork_status);
	free(data->philos);
	free(data->threads);
	free(data->mutex_forks);
}
void	*manager_routine(void *arg)
{
	t_data	*data;
	int	i;

	i = 0;
	data = (t_data *)arg;
	while(data->philos_alive)
	{
		if (i > data->number_of_philosophers)
			i = 0;
		if (get_time() - data->philos[i].timer_last_meal >= data->time_to_die)
		{
			printf ("%d %d died",get_time(), data->philos[i]);
			data->philos_alive = 0;
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	take_left_fork(t_philo *philo, int fork)
{
	int	left_fork_id;
	int	right_fork_id;
	int	fork_index;

	left_fork_id = philo->id - 1;
	right_fork_id = philo->id % philo->data->number_of_philosophers;
	if (fork_index = 0)
		fork_index = left_fork_id;
	else
		fork_index = right_fork_id;
	while (philo->data->philos_alive)
	{
		if (philo->data->fork_status[fork_index] == 0)
			{
				pthread_mutex_lock(&philo->data->mutex_forks[fork_index]);

				pthread_mutex_lock(&philo->data->mutex_print);
				if (fork_index == 0)
					printf("%d %d has taken a left fork", get_time(), philo->id);
				else
					printf("%d %d has taken a right fork", get_time(), philo->id);
				pthread_mutex_unlock(&philo->data->mutex_print);

				philo->data->fork_status[fork_index] = 1;

				philo->data->philos->mutex_left_fork = &philo->data->mutex_forks[fork_index];
				break;
			}
	}
}

void	take_left_fork(t_philo *philo)
{
	int	left_fork_id;

	left_fork_id = philo->id - 1;
	while (philo->data->philos_alive)
	{
		if (philo->data->fork_status[left_fork_id] == 0)
			{
				pthread_mutex_lock(&philo->data->mutex_forks[left_fork_id]);
				pthread_mutex_lock(&philo->data->mutex_print);
				printf("%d %d has taken a left fork", get_time(), philo->id);
				philo->data->fork_status[left_fork_id] = 1;
				philo->data->philos->mutex_left_fork = &philo->data->mutex_forks[left_fork_id];
				pthread_mutex_unlock(&philo->data->mutex_print);
				break;
			}
	}
}

void	take_right_fork(t_philo *philo)
{
	int	right_fork_id;

	right_fork_id = philo->id % philo->data->number_of_philosophers;
	while (philo->data->philos_alive)
	{
		if (philo->data->fork_status[right_fork_id] == 0)
			{
				pthread_mutex_lock(&philo->data->mutex_forks[right_fork_id]);
				pthread_mutex_lock(&philo->data->mutex_print);
				printf("%d %d has taken a right fork", get_time(), philo->id);
				philo->data->fork_status[right_fork_id] = 1;
				philo->data->philos->mutex_left_fork = &philo->data->mutex_forks[right_fork_id];
				pthread_mutex_unlock(&philo->data->mutex_print);
				break;
			}
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("thinking...\n");
	pthread_mutex_unlock(&philo->data->mutex_print);
	while(1)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
}

void	eat(t_philo *philo)
{
	int	left_fork_id;
	int	right_fork_id;


	left_fork_id = philo->id - 1;
	right_fork_id = philo->id;
	if (philo->data->philos_alive)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%d %d eating", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		custom_usleep(1000);
		pthread_mutex_unlock(&philo->data->mutex_forks[left_fork_id]);
		philo->data->fork_status[left_fork_id] = 0;
		pthread_mutex_unlock(&philo->data->mutex_forks[right_fork_id]);
		philo->data->fork_status[right_fork_id] = 0;
	}

}

void	sleep()
{
	printf("sleeping...\n");
	custom_usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(philo->data->philos_alive)
	{
		take_forks(philo);
		eat(philo);
		sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;

	argument_checker(argc, argv);
	parsing(&data, argc, argv);
	init_all(&data);
	mutex_init(&data);
	philo_init(&data);
/* 	for(int i = 0; i < data.number_of_philosophers; i++)
		printf("ID: %d\n",data.philos[i].id); */
	threads_init(&data);
	thread_join(&data);
	mutex_destroy(&data);
	free_all(&data);

	printf("number of philosophers: %d\n", data.number_of_philosophers);
	printf("time to die: %d\n", data.time_to_die);
	printf("time to eat: %d\n", data.time_to_eat);
	printf("time to sleep: %d\n", data.time_to_sleep);
	if (argc == 6)
		printf("number of times each philosopher must eat: %d\n", \
			data.number_of_times_each_philosopher_must_eat);
	return (0);
}
