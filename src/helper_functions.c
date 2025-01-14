/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:37:16 by asplavni          #+#    #+#             */
/*   Updated: 2025/01/14 18:12:02 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * funtion for retreving current time in milliseconds.
 */
long	get_time(void)
{
	Time time_now;

	gettimeofday(&time_now, NULL);
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

long	elapsed_time(long start, long end)
{
	return (end - start);
}

/**
 * custom usleep function with more precision.
 */
void	custom_usleep(long	milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
	{
		usleep(10);
	}
}