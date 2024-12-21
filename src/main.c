/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/21 21:53:27 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void free_all(t_data *data)
{
	free (data->threads);
	// free ((void *)data->forks);
	free (data);
}

void	*routine(void *argv)
{
	(void)argv;

	printf("eating...\n");
	sleep(3);
	printf("sleeping...\n");
	sleep(3);
	printf("thinking...\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;

	argument_checker(argc, argv);
	parsing(&data, argc, argv);
	threads_init(&data);
	// mutex_init(&data);
	thread_join(&data);
	// mutex_destroy(&data);
	// free_all(&data);
	// free((void *)data.threads);

	printf("number of philosophers: %d\n", data.number_of_philosophers);
	printf("time to eat: %d\n", data.time_to_eat);
	printf("time to sleep: %d\n", data.time_to_sleep);
	printf("time to die: %d\n", data.time_to_die);
	if (argc == 6)
		printf("number of times each philosopher must eat: %d\n", \
			data.number_of_times_each_philosopher_must_eat);
	return (0);
}
