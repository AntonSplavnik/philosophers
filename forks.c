/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:11:41 by asplavni          #+#    #+#             */
/*   Updated: 2025/01/18 18:48:47 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
void	take_forks(t_philo *philo, int flag)
{
	int	left_fork;
	int	right_fork;
	int	fork_index;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->number_of_philosophers;
	if (flag = 0)
		fork_index = left_fork;
	else
		fork_index = right_fork;
	while (philo->data->philos_alive)
	{
		if (philo->data->fork_status[fork_index] == 0)
			{
				pthread_mutex_lock(&philo->data->mutex_forks[fork_index]);
				pthread_mutex_lock(&philo->data->mutex_print);
				if (fork_index == 0)
					printf("%d %d has taken a left fork", get_time(), philo->id);
				else
					printf("%d %d has taken a right fork", get_time(), philo->id);
				pthread_mutex_unlock(&philo->data->mutex_print);
				philo->data->fork_status[fork_index] = 1;
				break;
			}
	}
}

void	take_forks(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("thinking...\n");
	pthread_mutex_unlock(&philo->data->mutex_print);
	while(philo->data->philos_alive)
	{
		take_forks(philo, 0);
		take_forks(philo, 1);
	}
} */