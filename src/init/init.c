/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:47:38 by asplavni          #+#    #+#             */
/*   Updated: 2024/12/04 22:07:52 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	(void)arg;
	printf("eating...\n");
	sleep(3);
	printf("sleeping...\n");
	return (NULL);
}

void	thread_create(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	philos->philos = malloc(data->number_of_philosophers * sizeof(pthread_t));
	if (philos == NULL)
		exit (1);
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos->philos[i], NULL, &routine, NULL) != 0)
		{
			free(philos);
			exit (1);
		}
		i++;
	}
}

void	thread_join(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philos->philos[i], NULL) != 0)
		{
			free(philos);
			exit (1);
		}
		i++;
	}
}

void	init_threads(t_data *data, t_philos *philos)
{
	thread_create(data, philos);
	thread_join(data, philos);
	free(philos->philos);
}
