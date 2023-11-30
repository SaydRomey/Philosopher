/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/30 13:59:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
idea: int hungry_philos;
each time a philo is full, hungry philo --;
if hungry philo == 0, print everyone is full;
*/

void	handle_dead(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	pthread_mutex_lock(&info->death_mutex);
	info->dead_philo = TRUE;
	pthread_mutex_unlock(&info->death_mutex);
	log_death(philo_time(), philo->id);
}

static int	not_dead_just_full(t_philo *philo)
{
	t_info	*info;
	int		dead;
	int		full;

	info = call_info();
	pthread_mutex_lock(&info->death_mutex);
	dead = info->dead_philo;
	pthread_mutex_unlock(&info->death_mutex);
	if (dead)
		return (FALSE);
	pthread_mutex_lock(&info->meal_mutex);
	if (info->meal_goal > 0 && philo->meals_eaten >= info->meal_goal)
		full = TRUE;
	else
		full = FALSE;
	pthread_mutex_unlock(&info->meal_mutex);
	return (full);
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
			{
				printf("not dead just full [%d]\n", philo->id);
				return ;
			}
			else if (philo_time() - philo->last_meal_time >= info->time_to_die) // starvation() ?
				return (handle_dead(philo));
			// pthread_mutex_unlock(&info->death_mutex);
			i++;
		}
		// usleep(40); // ?
		spend_time(1);
	}
}

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

