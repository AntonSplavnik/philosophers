/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/19 02:30:52 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->number_of_philosophers)
	{
		if (data->fork_status[i] == 1)
			pthread_mutex_unlock(&data->mutex_forks[i]);
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_timer);

	free(data->fork_status);
	free(data->philos);
	free(data->threads);
	free(data->mutex_forks);
}

void free_data(t_data *data)
{
	free(data->fork_status);
	free(data->philos);
	free(data->threads);
	free(data->mutex_forks);
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
				philo->data->fork_status[left_fork_id] = 1;
				pthread_mutex_lock(&philo->data->mutex_print);
				printf("%ld %d has taken a left fork\n", get_time(), philo->id);
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
				philo->data->fork_status[right_fork_id] = 1;
				pthread_mutex_lock(&philo->data->mutex_print);
				printf("%ld %d has taken a right fork\n", get_time(), philo->id);
				pthread_mutex_unlock(&philo->data->mutex_print);
				break;
			}
	}
}

void take_forks(t_philo *philo) {
    int left_fork_id = philo->id - 1;
    int right_fork_id = philo->id % philo->data->number_of_philosophers;

    pthread_mutex_lock(&philo->data->mutex_print);
    printf("%ld %d is thinking\n", get_time(), philo->id);
    pthread_mutex_unlock(&philo->data->mutex_print);

    while (philo->data->philos_alive) {
        // Try to take the forks in a specific order
        if (philo->id % 2 == 0) { // Even philosophers take left fork first
            if (pthread_mutex_lock(&philo->data->mutex_forks[left_fork_id]) == 0) {
                philo->data->fork_status[left_fork_id] = 1;

                pthread_mutex_lock(&philo->data->mutex_print);
                printf("%ld %d has taken a left fork\n", get_time(), philo->id);
                pthread_mutex_unlock(&philo->data->mutex_print);

                if (pthread_mutex_lock(&philo->data->mutex_forks[right_fork_id]) == 0) {
                    philo->data->fork_status[right_fork_id] = 1;

                    pthread_mutex_lock(&philo->data->mutex_print);
                    printf("%ld %d has taken a right fork\n", get_time(), philo->id);
                    pthread_mutex_unlock(&philo->data->mutex_print);

                    return; // Successfully took both forks
                }

                // Release left fork if right fork cannot be taken
                pthread_mutex_unlock(&philo->data->mutex_forks[left_fork_id]);
                philo->data->fork_status[left_fork_id] = 0;
            }
        } else { // Odd philosophers take right fork first
            if (pthread_mutex_lock(&philo->data->mutex_forks[right_fork_id]) == 0) {
                philo->data->fork_status[right_fork_id] = 1;

                pthread_mutex_lock(&philo->data->mutex_print);
                printf("%ld %d has taken a right fork\n", get_time(), philo->id);
                pthread_mutex_unlock(&philo->data->mutex_print);

                if (pthread_mutex_lock(&philo->data->mutex_forks[left_fork_id]) == 0) {
                    philo->data->fork_status[left_fork_id] = 1;

                    pthread_mutex_lock(&philo->data->mutex_print);
                    printf("%ld %d has taken a left fork\n", get_time(), philo->id);
                    pthread_mutex_unlock(&philo->data->mutex_print);

                    return; // Successfully took both forks
                }

                // Release right fork if left fork cannot be taken
                pthread_mutex_unlock(&philo->data->mutex_forks[right_fork_id]);
                philo->data->fork_status[right_fork_id] = 0;
            }
        }

        custom_usleep(1); // Small delay to prevent busy waiting
    }
}


// void	take_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->mutex_print);
// 	printf("%ld %d is thinking\n", get_time(), philo->id);
// 	pthread_mutex_unlock(&philo->data->mutex_print);
// 	while(philo->data->philos_alive)
// 	{
// 		take_left_fork(philo);
// 		take_right_fork(philo);
// 	}
// }

void	eat(t_philo *philo)
{
	int	left_fork_id;
	int	right_fork_id;

	left_fork_id = philo->id - 1;
	right_fork_id = philo->id % philo->data->number_of_philosophers;
	if (philo->data->philos_alive)
	{
		philo->timer_last_meal = get_time();
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %d is eating\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		custom_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->mutex_forks[left_fork_id]);
		philo->data->fork_status[left_fork_id] = 0;
		pthread_mutex_unlock(&philo->data->mutex_forks[right_fork_id]);
		philo->data->fork_status[right_fork_id] = 0;
	}
}

void	p_sleep(t_philo *philo)
{
	if (philo->data->philos_alive)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %d is sleeping\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		custom_usleep(philo->data->time_to_sleep);
	}
}

void	*manager_routine(void *arg)
{
	t_data	*data;
	int	i;

	i = 0;
	data = (t_data *)arg;
	while(data->philos_alive)
	{

		if (i >= data->number_of_philosophers)
			i = 0;
		pthread_mutex_lock(&data->mutex_timer);
		if (get_time() - data->philos[i].timer_last_meal >= data->time_to_die)
		{
			pthread_mutex_lock(&data->mutex_print);
			printf ("%ld %d died\n",get_time(), data->philos[i].id);
			pthread_mutex_unlock(&data->mutex_print);
			data->philos_alive = 0;
			pthread_mutex_unlock(&data->mutex_timer);
			return (NULL);
		}
		pthread_mutex_unlock(&data->mutex_timer);
		i++;
		custom_usleep(1);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(philo->data->philos_alive)
	{
		take_forks(philo);
		eat(philo);
		p_sleep(philo);
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
/* 	for(int i = 0; i < data.number_of_philosophers; i++)
		printf("ID: %d\n",data.philos[i].id); */
	threads_init(&data);
	thread_join(&data);
	mutex_destroy(&data);
	free_data(&data);

/* 	printf("number of philosophers: %d\n", data.number_of_philosophers);
	printf("time to die: %d\n", data.time_to_die);
	printf("time to eat: %d\n", data.time_to_eat);
	printf("time to sleep: %d\n", data.time_to_sleep);
	if (argc == 6)
		printf("number of times each philosopher must eat: %d\n", \
			data.number_of_times_each_philosopher_must_eat); */
	return (0);
}
