/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:55:07 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/09 01:31:31 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_is_positive_int(char *arg);

int	args_are_valid(int argc, char **argv, char **reason)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (*reason = ERR_ARGC, FALSE);
	i = 1;
	while (i < argc)
	{
		if (args_is_positive_int(argv[i]) == FALSE)
			return (*reason = ERR_ARG_INT, FALSE);
		i++;
	}
	if (ft_atol(argv[1]) > PHILO_MAX)
		return (*reason = ERR_PHILO_MAX, FALSE);
	return (TRUE);
}

static int	args_is_positive_int(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) || i > 9)
			return (FALSE);
		i++;
	}
	if (ft_atol(arg) <= 0 || ft_atol(arg) > INT_MAX)
		return (FALSE);
	return (TRUE);
}
