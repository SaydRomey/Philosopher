/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:31:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 21:44:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_to_eat(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->forks[philo->left_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK);
	pthread_mutex_lock(&info->forks[philo->right_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK);
	// 
	log_state_change(philo_time(), philo->id, LOG_EAT);
	pthread_mutex_lock(&info->meal_time);
	philo->last_meal_time = philo_time();
	info->total_meal_count++;
	pthread_mutex_unlock(&info->meal_time);
	spend_time(info->time_to_eat);
	pthread_mutex_unlock(&info->forks[philo->left_fork]);
	pthread_mutex_unlock(&info->forks[philo->right_fork]);
	// 
	spend_time(info->time_to_sleep);
	log_state_change(philo_time(), philo->id, LOG_SLEEP);
	return ;
}

static int	dining_is_over(void)
{
	t_info	*info;
	int		meals_eaten;

	info = call_info();
	if (info->meal_goal != -1)
	{
		pthread_mutex_lock(&info->meal_time);
		meals_eaten = info->total_meal_count;
		pthread_mutex_unlock(&info->meal_time);
		if (meals_eaten >= info->meal_goal)
			return (TRUE);
	}
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
		// log_state_change(philo_time(), philo->id, LOG_THINK);
		spend_time(info->time_to_eat);
	}
	while (TRUE)
	{
		if (dining_is_over())
			break ;
		pthread_mutex_lock(&info->philo_state);
		if (info->dead_philo == TRUE)
		{
			pthread_mutex_unlock(&info->philo_state);
			break ;
		}
		pthread_mutex_unlock(&info->philo_state);
		time_to_eat(philo);
		log_state_change(philo_time(), philo->id, LOG_THINK);
	}
	return (NULL);
}
