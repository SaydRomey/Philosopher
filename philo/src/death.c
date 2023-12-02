/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:35:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/01 22:01:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	no_one_is_dead(t_info *info)
{
	int	dead;

	// lock_mutex(&info->death_mutex, "[death_mutex] (%s, l.%d)", __FILE__, __LINE__);
	pthread_mutex_lock(&info->death_mutex);
	dead = info->dead_philo;
	// unlock_mutex(&info->death_mutex, "[death_mutex] (%s, l.%d)", __FILE__, __LINE__);
	pthread_mutex_unlock(&info->death_mutex);
	if (dead)
		return (FALSE);
	return (TRUE);
}

void	handle_dead(t_philo *philo)
{
	t_info	*info;

	info = call_info();
	// lock_mutex(&info->death_mutex, "[death_mutex] (%s, l.%d)", __FILE__, __LINE__);
	pthread_mutex_lock(&info->death_mutex);
	info->dead_philo = TRUE;
	// unlock_mutex(&info->death_mutex, "[death_mutex] (%s, l.%d)", __FILE__, __LINE__);
	pthread_mutex_unlock(&info->death_mutex);
	log_death(philo_time(), philo->id);
}
/*
	if (philo->last_meal + info->time_to_die < philo_time())
		starved = TRUE;
	else
		starved = FALSE;
*/
int	someone_starved(t_philo *philo)
{
	t_info	*info;
	long	now;
	long	last_meal;
	int		starved;

	info = call_info();
	now = philo_time();
	// lock_mutex(&info->meal_mutex, "[meal_mutex] (%s, l.%d)", __FILE__, __LINE__);
	pthread_mutex_lock(&info->meal_mutex);
	last_meal = philo->last_meal_time;
	// unlock_mutex(&info->meal_mutex, "[meal_mutex] (%s, l.%d)", __FILE__, __LINE__);
	pthread_mutex_unlock(&info->meal_mutex);
	if (no_one_is_dead(info) && now - last_meal > info->time_to_die)
		starved = TRUE;
	else
		starved = FALSE;
	return (starved);
}

/*
routine for 'coroner' thread in each philo's looping routine
*/
void	*check_for_dead(void *arg)
{
	t_philo			*philo;
	t_info			*info;

	philo = (t_philo *)arg;
	info = call_info();
	spend_time(info->time_to_die + 1);
	// lock_mutex(&info->end_mutex, "[end_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_lock(&info->end_mutex);
	if (someone_starved(philo))
	{
		handle_dead(philo);
	}
	// unlock_mutex(&info->end_mutex, "[end_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_unlock(&info->end_mutex);
	return (NULL);
}

// static int	not_dead_just_full(t_philo *philo)
// {
// 	t_info	*info;
// 	int		dead;
// 	int		full;

// 	info = call_info();
// 	pthread_mutex_lock(&info->death_mutex);
// 	dead = info->dead_philo;
// 	pthread_mutex_unlock(&info->death_mutex);
// 	if (dead)
// 		return (FALSE);
// 	pthread_mutex_lock(&info->meal_mutex);
// 	if (info->meal_goal > 0 && philo->meals_eaten >= info->meal_goal)
// 		full = TRUE;
// 	else
// 		full = FALSE;
// 	pthread_mutex_unlock(&info->meal_mutex);
// 	return (full);
// }
