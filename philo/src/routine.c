/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:31:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/30 13:45:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// change structure..
static int	dining_is_over(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->meal_mutex);
	if (info->meal_goal > 0 && philo->meals_eaten >= info->meal_goal)
	{
		pthread_mutex_unlock(&info->meal_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&info->meal_mutex);
	return (FALSE);
}

void	take_forks(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->forks[philo->left_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK "\t(left)", NULL);
	pthread_mutex_lock(&info->forks[philo->right_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK "\t(right)", NULL);
}

void	time_to_eat(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	log_state_change(philo_time(), philo->id, LOG_EAT, NULL);
	pthread_mutex_lock(&info->meal_mutex);
	philo->last_meal_time = philo_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&info->meal_mutex);
	spend_time(info->time_to_eat);
	pthread_mutex_unlock(&info->forks[philo->left_fork]);
	// log_state_change(philo_time(), philo->id, "dropped a fork\t(left)", NULL); //tmp
	pthread_mutex_unlock(&info->forks[philo->right_fork]);
	// log_state_change(philo_time(), philo->id, "dropped a fork\t(right)", NULL); //tmp
}

void	time_to_sleep(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	log_state_change(philo_time(), philo->id, LOG_SLEEP, NULL);
	spend_time(info->time_to_sleep);
	log_state_change(philo_time(), philo->id, LOG_THINK, NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_info		*info;

	info = call_info();
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		// log_state_change(philo_time(), philo->id, LOG_THINK, NULL); // maybe
		spend_time(info->time_to_eat);
	}
	while (no_one_is_dead(info))
	{
		take_forks(philo);
		time_to_eat(philo);
		if (dining_is_over(philo))
		{
			log_state_change(philo_time(), philo->id, LOG_FULL, GREEN);
			break ;
		}
		time_to_sleep(philo);
	}
	return (NULL);
}
