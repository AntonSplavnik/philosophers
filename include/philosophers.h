/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonsplavnik <antonsplavnik@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:54:30 by antonsplavn       #+#    #+#             */
/*   Updated: 2025/01/25 05:32:35 by antonsplavn      ###   ########.fr       */
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
typedef struct	s_philo t_philo;
typedef struct	s_data t_data;

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
	int				num_of_times_each_philo_must_eat;

	int				philos_alive;
	int				*fork_status;

	t_philo			*philos;

	pthread_t		thread_manager;
	pthread_t		*threads;

	pthread_mutex_t	mutex_has_eaten;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_is_alive;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_forks;
}	t_data;


// main.c
int		main(int argc, char **argv);

// corner_cases.c
int		corner_cases(t_data *data);

// parsing.c
int		parsing(t_data *philo, int argc, char **argv);

// init.c
void	data_init(t_data *data);
int		philo_init(t_data *data);
int		mutex_init(t_data *data);
int		threads_init(t_data *data);

// actions_core.c
int		eat(t_philo *philo);
int		p_sleep(t_philo *philo);

// actions_forks.c
int		take_forks(t_philo *philo);

// cleanaup.c
void	free_data(t_data *data);
void	thread_join(t_data *data);
void	mutex_destroy(t_data *data);

// routines.c
void	*manager_routine(void *arg);
void	*philo_routine(void *arg);
int		check_philos_alive(t_philo *philo);

// status.c
int		philo_death_status(t_data *data, int i);
int		philo_food_count_status(t_data *data);

// utils.c
long	get_time(void);
long	elapsed_time(long start, long end);
void	custom_usleep(long	milliseconds);
void	print_message(t_philo *philo, const char *message);

// input_validation.c
int		validate_arguments(int argc, char **argv);
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
