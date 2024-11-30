/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:52:24 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/11/30 22:30:04 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	process_and_validate_argument(char *argv)
{
	if (input_restrictions(argv) == 1
		|| limits(ft_atoi(argv)) == 1)
		return (1);
	return (0);
}

void	parsing(t_philo *philo, char **argv)
{
	empty_argument_checker(argv);
	if (process_and_validate_argument(argv[1]) == 0)
		philo->number_of_philosophers = ft_atoi(argv[1]);
	else if (process_and_validate_argument(argv[2]) == 0)
		philo->time_to_die = ft_atoi(argv[2]);
	else if (process_and_validate_argument(argv[3]) == 0)
		philo->time_to_eat = ft_atoi(argv[3]);
	else if (process_and_validate_argument(argv[4]) == 0)
		philo->time_to_sleep = ft_atoi(argv[4]);
	else if (process_and_validate_argument(argv[5]) == 0)
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		ft_putstr("Erorr in parsing");
}
