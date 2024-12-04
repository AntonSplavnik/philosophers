/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:54:30 by antonsplavn       #+#    #+#             */
/*   Updated: 2024/12/04 21:57:25 by asplavni         ###   ########.fr       */
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

typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_data;

typedef struct s_philos
{
	pthread_t	*philos;

}	t_philos;

// main.c
int		main(int argc, char **argv);

// parsing.c
int		process_and_validate_argument(char *argv);
void	parsing(t_data *philo, int argc, char **argv);

// parsing_utils.c
void	argument_checker(int argc, char **argv);
int		input_restrictions_helper(char *input_str, int i);
int		input_restrictions(char *input_str);
int		limits(long number);

// utils 2


// utils
void	ft_putstr(char *str);
void	ft_bzero(void *str, size_t number);
void	*ft_calloc(size_t num, size_t size);
int		ft_atoi(char *input_str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strcmp(char *input1, char *input2);

// ft_split
char	**ft_split(char *input, char c);

//init
void	init_threads(t_data *data, t_philos *philos);

#endif
