/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:21:23 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 21:19:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
uses mutex 'log_msg'
(mutex 'philo_state' is already locked by 'handle_dead()')
prints last message (if a philo died)
*/
void	log_death(long time, int id)
{
	t_info	*info;
	long	now;

	info = call_info();
	pthread_mutex_lock(&info->log_msg);
	now = time - info->start_time;
	printf("%ld %d %s\n", now, id, LOG_DIED);
	pthread_mutex_unlock(&info->log_msg);
}

/*
uses mutexes 'log_msg' and 'philo_state'
to print state change if no philo is dead
*/
void	log_state_change(long time, int id, char *state)
{
	t_info	*info;
	long	now;
	int		dead;

	info = call_info();
	pthread_mutex_lock(&info->log_msg);
	now = time - info->start_time;
	pthread_mutex_lock(&info->philo_state);
	dead = info->dead_philo;
	pthread_mutex_unlock(&info->philo_state);
	if (dead == FALSE)
		printf("%ld %d %s\n", now, id, state);
	pthread_mutex_unlock(&info->log_msg);
}
