/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/04 22:07:21 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philos	philos;

	argument_checker(argc, argv);
	parsing(&data, argc, argv);
	init_threads(&data, &philos);

	printf("philo.number_of_philosophers: %d\n", data.number_of_philosophers);
	printf("philo.time_to_eat: %d\n", data.time_to_eat);
	printf("philo.time_to_sleep: %d\n", data.time_to_sleep);
	printf("philo.time_to_die: %d\n", data.time_to_die);
	if (argc == 6)
		printf("philo.number_of_times_each_philosopher_must_eat: %d\n", data.number_of_times_each_philosopher_must_eat);
	return (0);
}
