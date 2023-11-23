/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:51:57 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 10:50:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	struct timeval	now;
	long			elapsed;

	gettimeofday(&now, NULL);
	elapsed = timeval_diff(call_param()->start_time, now);
	pthread_mutex_lock(&call_param()->log_msg);
	printf("%ld %d %s\n", elapsed, philo->id, status);
	pthread_mutex_unlock(&call_param()->log_msg);
}

void	time_to_eat(t_philo *philo)
{
	struct timeval	now;
	long			elapsed;
	
	gettimeofday(&now, NULL);
	elapsed = timeval_diff(philo->last_meal, now);
	if (elapsed > call_param()->time_to_die)
	{
		print_status(philo, LOG_DIED);
		call_param()->dead_philo = philo->id;
		return ;
	}
	print_status(philo, LOG_EAT);
	spend_time(call_param()->time_to_eat);
	philo->last_meal = now;
}

void	time_to_sleep(t_philo *philo)
{
	if (call_param()->dead_philo != 0)
		return ;
	print_status(philo, LOG_SLEEP);
	spend_time(call_param()->time_to_sleep);
}

void	time_to_think(t_philo *philo)
{
	if (call_param()->dead_philo != 0)
		return ;
	print_status(philo, LOG_THINK);
}

static void	init_philos(t_philo *philos, int philo_count)
{
	int				i;
	struct timeval	init_time;

	i = 0;
	gettimeofday(&init_time, NULL);
	while (i < philo_count)
	{
		philos[i].id = i + 1;
		philos[i].meal_count = 0;
		philos[i].last_meal = init_time;
		pthread_mutex_init(&philos[i].left_fork, NULL);
		if (i > 0)
			philos[i].right_fork = &philos[i - 1].left_fork;
		else
			philos[i].right_fork = &philos[philo_count - 1].left_fork;
		i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (call_param()->dead_philo == 0)
	{
		if (philo->meal_count == call_param()->meal_count)
			break ;
		else if (call_param()->meal_count != -1)
			philo->meal_count++;
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, LOG_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, LOG_FORK);
		time_to_eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return (NULL);
}

int	setup_philos(t_philo **philos)
{
	int	i;
	int	philo_count;

	philo_count = call_param()->philo_count;
	*philos = (t_philo *)malloc(sizeof(t_philo) * philo_count);
	if (!*philos)
		return (set_error_msg("Malloc failed"), 1);
	init_philos(*philos, philo_count);
	i = 0;
	while (i < philo_count)
	{
		if (pthread_create(&(*philos)[i].thread, NULL, \
			philo_routine, &(*philos)[i]) != 0)
		{
			free(*philos);	
			return (set_error_msg("Failed to create thread"), 1);
		}
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_join((*philos)[i].thread, NULL);
		i++;
	}
	return (0);
}
