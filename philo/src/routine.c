/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:31:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/29 22:51:00 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_eat(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	//
	pthread_mutex_lock(&info->forks[philo->left_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK);
	pthread_mutex_lock(&info->forks[philo->right_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK);
	//
	log_state_change(philo_time(), philo->id, LOG_EAT);
	pthread_mutex_lock(&info->meal_time);
	philo->last_meal_time = philo_time();
	pthread_mutex_unlock(&info->meal_time);
	spend_time(info->time_to_eat);
	log_state_change(philo_time(), philo->id, LOG_SLEEP);
	pthread_mutex_unlock(&info->forks[philo->right_fork]);
	pthread_mutex_unlock(&info->forks[philo->left_fork]);
}

static int	dining_is_over(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->meal_time);
	philo->meals_eaten++;
	if (info->meal_goal != -1 && philo->meals_eaten >= info->meal_goal)
	{
		pthread_mutex_unlock(&info->meal_time);
		return (TRUE);
	}
	pthread_mutex_unlock(&info->meal_time);
	return (FALSE);

}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	info = call_info();
	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
	{
		log_state_change(philo_time(), philo->id, LOG_THINK);
		spend_time(info->time_to_eat);
	}
	while (TRUE)
	{
		time_to_eat(philo);
		if (dining_is_over(philo))
			philo->full = TRUE;
		spend_time(info->time_to_sleep);
		if (death_happened(info) || philo->full == TRUE)
			return (NULL);
		log_state_change(philo_time(), philo->id, LOG_THINK);
		if (death_happened(info) || philo->full == TRUE)
			return (NULL);
	}
	return (NULL); // or arg? (never reached ?)
}
