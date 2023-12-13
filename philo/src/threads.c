/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:22:43 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 13:53:17 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
creates the thread that checks the vitals of each philo,
and each philo thread
*/
int	create_threads(t_philo *philo_ptr, pthread_t *coroner)
{
	int		i;
	int		ok;
	t_philo	*philo;

	if (pthread_create(coroner, NULL, check_for_dead, philo_ptr) != SUCCESS)
		return (set_error_msg(ERR_THREAD_CREATE), FAILURE);
	i = 0;
	while (i < call_info()->number_of_philos)
	{
		philo = &philo_ptr[i];
		ok = pthread_create(&philo->thread, NULL, routine, philo);
		if (ok != 0)
		{
			set_error_msg(ERR_THREAD_CREATE);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	wait_for_threads(t_philo *philo_ptr, pthread_t *coroner)
{
	int		i;
	int		ok;
	t_philo	*philo;

	i = 0;
	while (i < call_info()->number_of_philos)
	{
		philo = &philo_ptr[i];
		ok = pthread_join(philo->thread, NULL);
		if (ok != 0)
		{
			set_error_msg(ERR_THREAD_JOIN);
			return (FAILURE);
		}
		i++;
	}
	if (pthread_join(*coroner, NULL) != SUCCESS)
		return (set_error_msg(ERR_THREAD_JOIN), FAILURE);
	return (SUCCESS);
}
