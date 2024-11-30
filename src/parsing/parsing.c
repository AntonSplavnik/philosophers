/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:52:24 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/01 00:32:37 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parsing(t_philo *philo, int argc, char **argv)
{
	empty_argument_checker(argv);
	if (input_restrictions(argv[1]) == 0 && limits(ft_atoi(argv[1])) == 0)
		philo->number_of_philosophers = ft_atoi(argv[1]);
	if (input_restrictions(argv[2]) == 0 && limits(ft_atoi(argv[2])) == 0)
		philo->time_to_die = ft_atoi(argv[2]);
	if (input_restrictions(argv[3]) == 0 && limits(ft_atoi(argv[3])) == 0)
		philo->time_to_eat = ft_atoi(argv[3]);
	if (input_restrictions(argv[4]) == 0 && limits(ft_atoi(argv[4])) == 0)
		philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (input_restrictions(argv[5]) == 0 && limits(ft_atoi(argv[5])) == 0)
			philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
}