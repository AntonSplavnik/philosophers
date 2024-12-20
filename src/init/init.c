/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:47:38 by asplavni          #+#    #+#             */
/*   Updated: 2024/12/20 18:09:08 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threads_init(t_data *data, t_philos *philos)
{
	int	i;

	i = 0;
	philos->id = malloc(data->number_of_philosophers * sizeof(pthread_t));
	if (philos == NULL)
		exit (1);
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos->id[i], NULL, &routine, NULL) != 0)
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
		if (pthread_join(philos->id[i], NULL) != 0)
		{
			free(philos);
			exit (1);
		}
		i++;
	}
}

void	mutax_init(void)
{

}
