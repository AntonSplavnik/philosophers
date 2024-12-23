/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:54:30 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/23 20:06:47 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philos
{
	int	id;
	int	is_dead;
	int	has_eaten;
	int	started_eating;

}	t_philos;

typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;

	t_philos *philos;

	pthread_t	*threads;\
	pthread_mutex_t	*forks;

}	t_data;



// main.c
void	free_all(t_data *data);
void	*routine(void *arg);
int		main(int argc, char **argv);

//init
void	philo_init(t_data *data);
void	threads_init(t_data *data);
void	thread_join(t_data *data);
void	mutex_init(t_data *data);
void	mutex_destroy(t_data *data);


// parsing.c
void	parsing(t_data *philo, int argc, char **argv);

// parsing_utils.c
void	argument_checker(int argc, char **argv);
int		input_restrictions_helper(char *input_str, int i);
int		input_restrictions(char *input_str);
int		limits(long number);

// utils
void	ft_putstr(char *str);
void	ft_bzero(void *str, size_t number);
void	*ft_calloc(size_t num, size_t size);
int		ft_atoi(char *input_str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strcmp(char *input1, char *input2);

// utils 2

// ft_split
char	**ft_split(char *input, char c);


#endif
