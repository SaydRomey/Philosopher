/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:22:43 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 14:50:37 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;
	printf("thread created\n");
	return (NULL);
}

int	create_threads(t_philo *philo)
{
	int	i;
	int	ok;

	i = 0;
	while (i < call_info()->number_of_philos)
	{
		ok = pthread_create(&philo[i].thread, NULL, routine, NULL);
		if (ok != 0)
		{
			set_error_msg(ERR_THREAD_CREATE);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	wait_for_threads(t_philo *philo)
{
	int	i;
	int	ok;

	i = 0;
	while (i < call_info()->number_of_philos)
	{
		ok = pthread_join(philo[i].thread, NULL);
		if (ok != 0)
		{
			printf("Failed to join thread\n");
			return ;
		}
		i++;
	}
}
