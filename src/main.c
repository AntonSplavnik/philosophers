/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/04 19:21:25 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	argument_checker(argc, argv);
	parsing(&philo, argc, argv);

	printf("philo.number_of_philosophers: %d\n", philo.number_of_philosophers);
	printf("philo.time_to_eat: %d\n", philo.time_to_eat);
	printf("philo.time_to_sleep: %d\n", philo.time_to_sleep);
	printf("philo.time_to_die: %d\n", philo.time_to_die);
	if (argc == 6)
		printf("philo.number_of_times_each_philosopher_must_eat: %d\n", philo.number_of_times_each_philosopher_must_eat);
	return (0);
}
