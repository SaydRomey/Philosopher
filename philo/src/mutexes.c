/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:15:04 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/09 23:13:08 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_forks(void);
static int	init_mutexes(void);

int	setup_mutexes(void)
{
	if (allocate_forks() != SUCCESS)
		return (FAILURE);
	if (init_mutexes() != SUCCESS)
		return (FAILURE);
	call_info()->mutex_flag = TRUE;
	return (SUCCESS);
}

static int	allocate_forks(void)
{
	t_info	*info;

	info = call_info();
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philos);
	if (!info->forks)
		return (set_error_msg(ERR_MALLOC), FAILURE);
	return (SUCCESS);
}

static int	init_mutexes(void)
{
	int		i;
	int		check;
	t_info	*info;

	i = 0;
	info = call_info();
	while (i < info->number_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != SUCCESS)
			return (set_error_msg(ERR_MUTEX_INIT), FAILURE);
		i++;
	}
	check = 0;
	check += pthread_mutex_init(&info->log_mutex, NULL);
	check += pthread_mutex_init(&info->meal_mutex, NULL);
	check += pthread_mutex_init(&info->death_mutex, NULL);
	if (check != SUCCESS)
		return (set_error_msg(ERR_MUTEX_INIT), FAILURE);
	return (SUCCESS);
}

int	destroy_mutexes(void)
{
	int		i;
	int		check;
	t_info	*info;

	i = 0;
	info = call_info();
	while (i < info->number_of_philos)
	{
		if (pthread_mutex_destroy(&info->forks[i]) != SUCCESS)
			return (set_error_msg(ERR_MUTEX_DESTROY), FAILURE);
		i++;
	}
	check = 0;
	check += pthread_mutex_destroy(&info->log_mutex);
	check += pthread_mutex_destroy(&info->meal_mutex);
	check += pthread_mutex_destroy(&info->death_mutex);
	if (check != SUCCESS)
		return (set_error_msg(ERR_MUTEX_DESTROY), FAILURE);
	return (SUCCESS);
}

/*
**for debugging*
usage:	lock_mutex(&info->mutex, "[nameof_mutex] (%s, l.%d)", __FILE__, __LINE__);

#include <stdarg.h>

void	lock_mutex(pthread_mutex_t *mutex, char *str, ...)
{
	va_list	args;

	printf(BLUE"Locking\t\t->"RESET);
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	printf("\n");
	pthread_mutex_lock(mutex);	
}
*/
