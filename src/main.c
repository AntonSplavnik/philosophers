/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/16 22:33:17 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_all(t_data *data)
{
	free(data->philos);
	free(data->threads);
	free(data->forks);
}
void	*manager_routine(void *arg)
{
	t_data	*data;
	int	i;

	i = 0;
	data = (t_data *)arg;
	while(data->philos_alive = 1)
	{
		if (i > data->number_of_philosophers)
			i = 0;
		if (get_time() - data->philos[i].timer_last_meal >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->print_death);
			printf ("died %d", data->philos[i]);
			pthread_mutex_unlock(&data->print_death);
			data->philos_alive = 0;
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	take_left_fork(void)
{

}

void	take_right_fork()
{

}

void	take_forks(void)
{
	printf("thinking...\n");
	while(1)
	{
		take_left_fork();
		take_right_fork();
	}
}

void	eat(void)
{
	printf("eating...\n");
	custom_usleep(1000);
}

void	sleep(void)
{
	printf("sleeping...\n");
	custom_usleep(1000);
}

void	think(void)
{

}



void	*philo_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while(data->philos_alive = 1)
	{
		take_forks();
		eat();
		sleep();
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
