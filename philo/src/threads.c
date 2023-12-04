/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:22:43 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/04 13:40:10 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo *philo_ptr)
{
	int		i;
	int		ok;
	t_philo	*philo;

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

int	wait_for_threads(t_philo *philo_ptr)
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
	return (SUCCESS);
}
