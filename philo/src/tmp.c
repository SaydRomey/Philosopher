/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:31:18 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/01 21:18:16 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tmp_log(char *msg, ...)
{
	t_info	*info;
	va_list	args;

	info = call_info();
	lock_mutex(&info->log_mutex, "[log_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_lock(&info->log_mutex);
	va_start(args, msg);
	vprintf(msg, args);
	va_end(args);
	unlock_mutex(&info->log_mutex, "[log_mutex] (%s, l.%d)", __FILE__, __LINE__);
	// pthread_mutex_unlock(&info->log_mutex);
}

void	print_info(void)
{
	t_info	*info;

	info = call_info();
	printf("\n");
	printf("philo count:\t%d\n", info->number_of_philos);
	printf("time to die:\t%ld\n", info->time_to_die);
	printf("time to eat:\t%ld\n", info->time_to_eat);
	printf("time to sleep:\t%ld\n", info->time_to_sleep);
	printf("meal goal:\t%d\n", info->meal_goal);
	printf("hungry philos:\t%d\n", info->hungry_philos);
	// 
	printf("fork_mutex:\t%p\n", info->forks);
	printf("log_mutex:\t%p\n", &info->log_mutex);
	printf("meal_mutex:\t%p\n", &info->meal_mutex);
	printf("death_mutex:\t%p\n", &info->death_mutex);
	// 
	printf("philo ptr:\t%p\n", info->philo_ptr);
	printf("dead_philo flag:\t%d\n", info->dead_philo);
	printf("start time:\t%ld\n", info->start_time);
	printf("current error_msg:\t%s\n", info->error_msg);
	printf("\n");
}

void	print_philo_info(t_philo *philo)
{
	int	i;

	i = 0;
	printf("\n");
	while (i < call_info()->number_of_philos)
	{
		printf("philo id:\t%d\n", philo[i].id);
		printf("philo index:\t%d\n", i);
		printf("lfork index:\t%d\n", philo[i].left_fork);
		printf("rfork index:\t%d\n", philo[i].right_fork);
		printf("last meal time:\t%ld\n", philo[i].last_meal_time);
		printf("meals eaten:\t%d\n", philo[i].meals_eaten);
		printf("thread:\t%p\n", &philo[i].thread);
		printf("\n");
		i++;
	}
}

/*
for testing purposes
**(usage: here(__FILE__, __LINE__);*
*/
void	here(char *file, int line)
{
	printf("HERE (%s, l.%d)\n", file, line);
}

/*
**for debugging*
usage:	lock_mutex(&info->mutex, "[nameof_mutex] (%s, l.%d)", __FILE__, __LINE__);
*/
void	lock_mutex(pthread_mutex_t *mutex, char *str, ...)
{
	va_list	args;

	printf(BLUE"LOCKING\t\t->"RESET);
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	printf("\n");
	pthread_mutex_lock(mutex);	
}

/*
**for debugging*
usage:	unlock_mutex(&info->mutex, "[nameof_mutex] (%s, l.%d)", __FILE__, __LINE__);
*/
void	unlock_mutex(pthread_mutex_t *mutex, char *str, ...)
{
	va_list	args;

	printf(BLUE"UNLOCKING\t->"RESET);
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	printf("\n");
	pthread_mutex_unlock(mutex);
}
