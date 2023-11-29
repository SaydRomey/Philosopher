/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/29 12:42:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_dead(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->philo_state);
	if (info->dead_philo == FALSE)
		// printf("%ld %d died\n", philo_time() - info->start_time, philo->id);
		log_death(philo_time(), philo->id);
	info->dead_philo = TRUE;
	pthread_mutex_unlock(&info->philo_state);
}

void	check_for_dead(t_philo *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;
	int		i;
	// int		meals;
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
			// meals = info->total_meal_count;
			pthread_mutex_unlock(&info->meal_time);
			// if (meals >= info->meal_goal)
			// 	return ;
			if (time >= info->time_to_die)
				return (handle_dead(philo));
			i++;
		}
	}
}
