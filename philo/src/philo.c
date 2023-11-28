/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:51:57 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 14:01:40 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	left_index(int index, int last_index)
{
	return ((index - 1 + last_index) % last_index);
}

static inline int	right_index(int index, int last_index)
{
	return ((index + 1) % last_index);
}

/*
handles the creation of the 't_philo' array
and returns SUCCESS (1) or FAILURE (0)
*/
int	setup_philos(t_philo **philo)
{
	int	i;
	int	number_of_philos;

	i = 0;
	number_of_philos = call_info()->number_of_philos;
	*philo = malloc(sizeof(t_philo) * number_of_philos);
	if (*philo == NULL)
		return (set_error_msg(ERR_MALLOC), FAILURE);
	while (i < number_of_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].left_fork = left_index(i, number_of_philos);
		(*philo)[i].right_fork = right_index(i, number_of_philos);
		(*philo)[i].last_meal_time = philo_time();
		(*philo)[i].meals_eaten = 0;
		i++;
	}
	return (SUCCESS);
}
