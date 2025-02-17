/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:50:49 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 05:07:46 by antonsplavn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_arguments(argc, argv))
		return (1);
	if (parsing(&data, argc, argv))
		return (1);
	if (corner_cases(&data))
		return (0);
	data_init(&data);
	if (mutex_init(&data))
		return (1);
	if (philo_init(&data))
		return (1);
	threads_init(&data);
	thread_join(&data);
	mutex_destroy(&data);
	free_data(&data);
	return (0);
}
