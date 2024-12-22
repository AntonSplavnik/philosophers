/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/22 13:56:59 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_all(t_data *data)
{
	free((void *)data->threads);
	free((void *)data->forks);
}

void	*routine(void *argv)
{
	(void)argv;

	printf("eating...\n");
	sleep(1);
	printf("sleeping...\n");
	sleep(1);
	printf("thinking...\n");
	sleep(1);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;

	argument_checker(argc, argv);
	parsing(&data, argc, argv);
	mutex_init(&data);
	threads_init(&data);
	thread_join(&data);
	mutex_destroy(&data);
	free_all(&data);

	printf("number of philosophers: %d\n", data.number_of_philosophers);
	printf("time to eat: %d\n", data.time_to_eat);
	printf("time to sleep: %d\n", data.time_to_sleep);
	printf("time to die: %d\n", data.time_to_die);
	if (argc == 6)
		printf("number of times each philosopher must eat: %d\n", \
			data.number_of_times_each_philosopher_must_eat);
	return (0);
}
