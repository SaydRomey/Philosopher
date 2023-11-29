/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 21:20:40 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_dead(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->philo_state);
	if (info->dead_philo == FALSE)
		log_death(philo_time(), philo->id);
	info->dead_philo = TRUE;
	pthread_mutex_unlock(&info->philo_state);
}

void	check_for_dead(t_philo *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;
	int		i;
	long	time;

	info = call_info();
	while (TRUE)
	{
		i = 0;
		while (i < info->number_of_philos)
		{
			philo = &philo_ptr[i];
			pthread_mutex_lock(&info->meal_time);
			time = philo_time() - philo->last_meal_time;
			pthread_mutex_unlock(&info->meal_time);
			if (time > info->time_to_die)
				return (handle_dead(philo));			
		}
	}
}
