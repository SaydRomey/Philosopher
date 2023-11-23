/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:54 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 10:32:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_param	*call_param(void)
{
	static t_param	*param;

	if (param == NULL)
	{
		param = malloc(sizeof(t_param));
		if (param == NULL)
			return (NULL);
	}
	return (param);
}

void	set_params(int argc, char **argv)
{
	t_param			*param;
	struct timeval	start_time;

	param = call_param();
	param->philo_count = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		param->meal_count = ft_atoi(argv[5]);
	else
		param->meal_count = -1;
	param->dead_philo = 0;
	gettimeofday(&start_time, NULL);
	param->start_time = start_time;
}

void	free_param(void)
{
	t_param	*param;

	param = call_param();
	free(param);
}

void	set_error_msg(char *msg)
{
	t_param	*param;

	param = call_param();
	if (param->error_msg)
		free(param->error_msg);
	param->error_msg = msg;
}

/*
*/
char	*get_error_msg(void)
{
	t_param	*param;

	param = call_param();
	return (param->error_msg);
}
