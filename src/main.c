/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/14 19:14:27 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_all(t_data *data)
{
	free(data->philos);
	free(data->threads);
	free(data->forks);
}
void	*manager_routine(void *data)
{
	(void) data;
	return (NULL);
}

void	*routine(void *arg)
{
	t_data *data = (t_data *)arg;

	// mutex
	for(int i = 0; i < data->number_of_philosophers; i++)
	{
		printf("")
	}

	printf("eating...\n");
	custom_usleep(1000);
	// mutex + 1
	printf("sleeping...\n");
	custom_usleep(1000);
	printf("thinking...\n");
	custom_usleep(1000);
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
