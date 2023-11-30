/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/29 22:50:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_dead(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_unlock(&info->philo_state);
	pthread_mutex_lock(&info->philo_state);
	info->dead_philo = TRUE;
	pthread_mutex_unlock(&info->philo_state);
	log_death(philo_time(), philo->id);
}

static int	not_dead_just_full(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->philo_state);
	if (philo->meals_eaten >= info->meal_goal) // or == ?
	{
		// philo->full = TRUE; //?
		pthread_mutex_unlock(&info->philo_state);
		return (TRUE);
	}
	// no unlocking ?
	return (FALSE);
}

void	check_for_dead(t_philo *philo_ptr)
{
	t_info	*info;
	t_philo	*philo;
	int		i;

	info = call_info();
	while (TRUE)
	{
		i = 0;
		while (i < info->number_of_philos)
		{
			philo = &philo_ptr[i];
			if (not_dead_just_full(philo))
				return ;
			else if (philo_time() - philo->last_meal_time >= info->time_to_die) // starvation() ?
				return (handle_dead(philo));
			pthread_mutex_unlock(&info->philo_state);
			i++;
		}
		// usleep(40); // ?
		spend_time(1);
	}
}

int	death_happened(t_info *info)
{
	pthread_mutex_lock(&info->philo_state);
	if (info->dead_philo == TRUE)
	{
		pthread_mutex_unlock(&info->philo_state);
		return (TRUE);
	}
	pthread_mutex_unlock(&info->philo_state);
	return (FALSE);
}

