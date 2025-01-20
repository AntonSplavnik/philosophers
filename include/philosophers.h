/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:54:30 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/18 22:49:57 by antonsplavn      ###   ########.fr       */
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
# include <sys/time.h>

typedef	struct	timeval	Time;
typedef struct s_philo t_philo;
typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int				has_eaten;
	long			timer_start;
	long			timer_last_meal;

	t_data			*data;

	pthread_mutex_t	*mutex_left_fork;
	pthread_mutex_t	*mutex_right_fork;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;

	int				philos_alive;
	int				*fork_status;

	t_philo			*philos;

	pthread_t		thread_manager;
	pthread_t		*threads;

	pthread_mutex_t	mutex_timer;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_forks;
}	t_data;


// main.c
void	cleanup_data(t_data *data);
void	free_data(t_data *data);
void	*philo_routine(void *arg);
void	*manager_routine(void *data);
int		main(int argc, char **argv);

// init
void	data_init(t_data *data);
void	philo_init(t_data *data);
void	threads_init(t_data *data);
void	thread_join(t_data *data);
void	mutex_init(t_data *data);
void	mutex_destroy(t_data *data);

// time.c
long	get_time(void);
long	elapsed_time(long start, long end);
void	custom_usleep(long	milliseconds);

// parsing.c
void	parsing(t_data *philo, int argc, char **argv);

// input_validation.c
void	validate_arguments(int argc, char **argv);
int		validate_characters(char *input_str, int i);
int		validate_input_string(char *input_str);
int		validate_number_limits(long number);

// utils
void	ft_putstr(char *str);
void	ft_bzero(void *str, size_t number);
void	*ft_calloc(size_t num, size_t size);
int		ft_atoi(char *input_str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strcmp(char *input1, char *input2);

// ft_split
char	**ft_split(char *input, char c);


#endif
