/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:21:23 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/30 13:27:09 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
uses mutex 'log_mutex'
(mutex 'death_mutex' is already locked by 'handle_dead()')
prints last message (if a philo died)
*/
void	log_death(long time, int id)
{
	t_info	*info;
	long	now;

	info = call_info();
	pthread_mutex_lock(&info->log_mutex);
	now = time - info->start_time;
	printf("%ld\t%d %s%s%s\n", now, id, RED, LOG_DIED, RESET);
	pthread_mutex_unlock(&info->log_mutex);
}

/*
uses mutexes 'log_mutex' and 'death_mutex'
to print state change if no philo is dead
**(use ANSI escape codes to print in color, or NULL)**
*/
void	log_state_change(long time, int id, char *state, char *color)
{
	t_info	*info;
	long	now;
	int		dead;

	info = call_info();
	pthread_mutex_lock(&info->log_mutex);
	now = time - info->start_time;
	now = now - (now % 10);
	pthread_mutex_lock(&info->death_mutex);
	dead = info->dead_philo;
	pthread_mutex_unlock(&info->death_mutex);
	if (dead == FALSE)
	{
		if (color)
			printf("%ld\t%d %s%s%s\n", now, id, color, state, RESET);
		else
			printf("%ld\t%d %s\n", now, id, state);
	}
	pthread_mutex_unlock(&info->log_mutex);
}
