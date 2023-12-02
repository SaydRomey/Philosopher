/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:31:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/01 20:01:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// change structure..
static int	dining_is_over(t_philo *philo)
{
	t_info	*info;
	int		full;

	info = call_info();
	lock_mutex(&info->meal_mutex, "[meal_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_lock(&info->meal_mutex);
	if (info->meal_goal > 0 && philo->meals_eaten >= info->meal_goal)
	{
		full = TRUE;
		log_state_change(philo_time(), philo->id, LOG_FULL, GREEN);
		info->hungry_philos--;
		if (info->hungry_philos == 0)
			log_misc("\nEveryone is "GREEN"full"RESET);
		// else
		// 	log_misc("\t"YELLOW"more philos to feed"RESET);
	}
	else
		full = FALSE;
	unlock_mutex(&info->meal_mutex, "[meal_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_unlock(&info->meal_mutex);
	return (full);
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
	lock_mutex(&info->meal_mutex, "[meal_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_lock(&info->meal_mutex);
	philo->last_meal_time = philo_time();
	philo->meals_eaten++;
	unlock_mutex(&info->meal_mutex, "[meal_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_unlock(&info->meal_mutex);
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
	// pthread_t	coroner; //test

	info = call_info();
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		// log_state_change(philo_time(), philo->id, LOG_THINK, NULL); // maybe
		spend_time(info->time_to_eat);
	}
	while (no_one_is_dead(info))
	{
		// pthread_create(&coroner, NULL, check_for_dead, philo); //test
		take_forks(philo);
		time_to_eat(philo);
		// pthread_detach(coroner); // test
		if (dining_is_over(philo))
			break ;
		time_to_sleep(philo);
	}
	return (NULL);
}
