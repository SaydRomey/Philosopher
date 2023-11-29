/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:54 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 12:38:57 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*call_info(void)
{
	static t_info	*info;

	if (info == NULL)
	{
		info = malloc(sizeof(t_info));
		if (info == NULL)
			return (set_error_msg(ERR_MALLOC), NULL);
	}
	return (info);
}

void	set_info(int argc, char **argv)
{
	t_info	*info;

	info = call_info();
	info->number_of_philos = (int)ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		info->meal_goal = ft_atol(argv[5]);
		info->meal_goal *= info->number_of_philos;
	}
	else
		info->meal_goal = -1;
	info->total_meal_count = 0;
	info->dead_philo = FALSE;
}

void	free_info(void)
{
	t_info	*info;

	info = call_info();
	destroy_mutexes();
	if (info->forks)
		free(info->forks);
	if (info->philo_ptr)
		free(info->philo_ptr);
	free(info);
}
