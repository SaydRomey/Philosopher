/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:55:07 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/04 10:16:04 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
returns FALSE (0) if 'arg' either contains a non-digit char
or is equal to 0 or greater than INT_MAX
*/
static int	args_is_positive_int(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FALSE);
		i++;
	}
	if (ft_atol(arg) == 0 || ft_atol(arg) > INT_MAX)
		return (FALSE);
	return (TRUE);
}

/*
returns FALSE (0) if 'argc' is not 5 or 6
or if any of the arguments is not a positive integer
or if the number of philosophers is greater than PHILO_MAX
**also sets the error message in 't_info' if any of the above is true*
*/
int	args_are_valid(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (set_error_msg(ERR_ARGC), FALSE);
	i = 1;
	while (i < argc)
	{
		if (args_is_positive_int(argv[i]) == FALSE)
			return (set_error_msg(ERR_ARG_INT), FALSE);
		i++;
	}
	if (ft_atol(argv[1]) > PHILO_MAX)
		return (set_error_msg(ERR_PHILO_MAX), FALSE);
	return (TRUE);
}
