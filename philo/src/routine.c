/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:31:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/09 02:12:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		take_forks(t_philo *philo);
static void		time_to_eat(t_philo *philo);
static void		time_to_sleep(t_philo *philo);
static int		dining_is_over(t_philo *philo);

void	*routine(void *arg)
{
	t_philo		*philo;
	t_info		*info;

	info = call_info();
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		spend_time(info->time_to_eat);
	}
	while (no_one_is_dead(info))
	{
		take_forks(philo);
		time_to_eat(philo);
		if (dining_is_over(philo))
			break ;
		time_to_sleep(philo);
	}
	return (NULL);
}

static int	dining_is_over(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->meal_mutex);
	if (info->meal_goal > 0 && philo->meals_eaten >= info->meal_goal)
	{
		philo->is_full = TRUE;
		log_state_change(philo_time(), philo->id, LOG_FULL, GREEN);
		info->hungry_philos--;
		if (info->hungry_philos == 0 && no_one_is_dead(info))
			log_misc("Everyone is "GREEN"full"RESET, 0);
	}
	else
	{
		philo->is_full = FALSE;
	}
	pthread_mutex_unlock(&info->meal_mutex);
	return (philo->is_full);
}

static void	take_forks(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->forks[philo->left_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK "\t(left)", NULL);
	pthread_mutex_lock(&info->forks[philo->right_fork]);
	log_state_change(philo_time(), philo->id, LOG_FORK "\t(right)", NULL);
}

static void	time_to_eat(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	log_state_change(philo_time(), philo->id, LOG_EAT, NULL);
	pthread_mutex_lock(&info->meal_mutex);
	philo->last_meal_time = philo_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&info->meal_mutex);
	spend_time(info->time_to_eat);
	pthread_mutex_unlock(&info->forks[philo->right_fork]);
	pthread_mutex_unlock(&info->forks[philo->left_fork]);
}

static void	time_to_sleep(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	log_state_change(philo_time(), philo->id, LOG_SLEEP, NULL);
	spend_time(info->time_to_sleep);
	log_state_change(philo_time(), philo->id, LOG_THINK, NULL);
}
