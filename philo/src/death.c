/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/04 14:08:09 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	no_one_is_dead(t_info *info)
{
	int	dead;

	pthread_mutex_lock(&info->death_mutex);
	dead = info->dead_philo;
	pthread_mutex_unlock(&info->death_mutex);
	if (dead)
		return (FALSE);
	return (TRUE);
}

void	handle_dead(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->death_mutex);
	info->dead_philo = TRUE;
	pthread_mutex_unlock(&info->death_mutex);
	log_death(philo_time(), philo->id);
}

int	someone_starved(t_philo *philo)
{
	t_info	*info;
	long	now;
	long	last_meal;
	int		starved;

	info = call_info();
	pthread_mutex_lock(&info->meal_mutex);
	now = philo_time();
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&info->meal_mutex);
	// if (no_one_is_dead(info) && now - last_meal > info->time_to_die) //check
	if (now - last_meal > info->time_to_die)
		starved = TRUE;
	else
		starved = FALSE;
	return (starved);
}

int	everyone_is_full(t_info *info)
{
	int	hungry;

	pthread_mutex_lock(&info->meal_mutex);
	hungry = info->hungry_philos;
	pthread_mutex_unlock(&info->meal_mutex);
	if (hungry == 0)
		return (TRUE);
	return (FALSE);
}

void	*check_for_dead(void *arg)
{
	t_philo	*philo;
	t_info	*info;
	int		i;

	philo = (t_philo *)arg;
	info = call_info();
	while (no_one_is_dead(info))
	{
		if (everyone_is_full(info))
			break ;
		i = 0;
		while (i < info->number_of_philos)
		{
			if (someone_starved(&philo[i]))
			{
				handle_dead(&philo[i]);
				return (NULL);
			}
			i++;
		}
		spend_time(42);
	}
	return (NULL);
}
