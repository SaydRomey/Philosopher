/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:15:04 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 14:08:17 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_forks(void)
{
	t_info	*info;

	info = call_info();
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philos);
	if (!info->forks)
		return (set_error_msg(ERR_MALLOC), FAILURE);
	return (SUCCESS);
}

int	init_mutexes(void)
{
	int		i;
	t_info	*info;

	i = 0;
	info = call_info();
	while (i < info->number_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != SUCCESS)
			return (set_error_msg(ERR_MUTEX_INIT), FAILURE);
		i++;
	}
	i = 0;
	i += pthread_mutex_init(&info->log_msg, NULL);
	i += pthread_mutex_init(&info->philo_state, NULL);
	i += pthread_mutex_init(&info->meal_time, NULL);
	if (i != SUCCESS)
		return (set_error_msg(ERR_MUTEX_INIT), FAILURE);
	return (SUCCESS);
}

int	setup_mutexes(void)
{
	if (allocate_forks() == FAILURE)
		return (FAILURE);
	if (init_mutexes() == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	destroy_mutexes(void)
{
	int		i;
	t_info	*info;

	i = 0;
	info = call_info();
	while (i < info->number_of_philos)
	{
		if (pthread_mutex_destroy(&info->forks[i]) != SUCCESS)
			return (set_error_msg(ERR_MUTEX_DESTROY), FAILURE);
		i++;
	}
	i = 0;
	i += pthread_mutex_destroy(&info->log_msg);
	i += pthread_mutex_destroy(&info->philo_state);
	i += pthread_mutex_destroy(&info->meal_time);
	if (i != SUCCESS)
		return (set_error_msg(ERR_MUTEX_DESTROY), FAILURE);
	return (SUCCESS);
}
