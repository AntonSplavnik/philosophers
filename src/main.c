/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/01 00:38:12 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc > 6)
		ft_putstr("Too many arguments. 5 - 6\n");
	else if (argc < 5)
	{
		ft_putstr("Not enough arguments. 5 - 6\n");
		return (0);
	}
	else
		parsing(&philo, argc, argv);

	printf("philo.number_of_philosophers: %d\n", philo.number_of_philosophers);
	printf("philo.time_to_eat: %d\n", philo.time_to_eat);
	printf("philo.time_to_sleep: %d\n", philo.time_to_sleep);
	printf("philo.time_to_die: %d\n", philo.time_to_die);
	if (argc == 6)
		printf("philo.number_of_times_each_philosopher_must_eat:\
			%d\n", philo.number_of_times_each_philosopher_must_eat);
	return (0);
}
