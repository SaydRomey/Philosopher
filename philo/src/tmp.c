/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:31:18 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/22 20:31:36 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
get current time in milliseconds (useful?)
*/
long	philo_time(void)
{
	struct timeval	time;
	long			milliseconds;

	if (gettimeofday(&time, NULL) == -1)
	{
		set_error_msg(ERR_TIMEOFDAY);
		return (-1);
	}
	milliseconds = (long)time.tv_sec * 1000;
	milliseconds += (long)time.tv_usec / 1000;
	return (milliseconds);
}


