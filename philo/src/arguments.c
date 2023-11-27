/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:55:07 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 12:42:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_is_positive_int(char *arg)
{
	int	i;

	i = 0;
	if (ft_atol(arg) == 0)
		return (FALSE);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	args_are_valid(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (set_error_msg(ERR_ARGC), FALSE);
	i = 1;
	while (i < argc)
	{
		if (!args_is_positive_int(argv[i]))
			return (set_error_msg(ERR_ARG_INT), FALSE);
		i++;
	}
	if (ft_atol(argv[1]) > PHILO_MAX)
		return (set_error_msg(ERR_PHILO_MAX), FALSE);
	return (TRUE);
}
