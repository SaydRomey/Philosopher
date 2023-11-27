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
			return (NULL);
	}
	return (info);
}

void	set_info(int argc, char **argv)
{
	t_info			*info;
	struct timeval	start_time;

	info = call_info();
	info->philo_count = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->meal_count = ft_atol(argv[5]);
	else
		info->meal_count = -1;
	info->dead_philo = 0;
	gettimeofday(&start_time, NULL);
	info->start_time = start_time;
}

void	free_info(void)
{
	t_info	*info;

	info = call_info();
	free(info);
}

void	set_error_msg(char *msg)
{
	t_info	*info;

	info = call_info();
	if (info->error_msg)
		free(info->error_msg);
	info->error_msg = msg;
}

/*
*/
char	*get_error_msg(void)
{
	t_info	*info;

	info = call_info();
	return (info->error_msg);
}
