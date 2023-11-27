/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:35:41 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 12:44:37 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	int		digit;
	long	result;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(str[i]))
	{
		digit = str[i] - '0';
		result = result * 10;
		result = result + digit;
		i++;
	}
	return (result * sign);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

/*
prints current error message in 't_info' to stderr,
frees the struct and returns 'exit_status'
*/
int	error(int exit_status)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(get_error_msg(), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_info();
	return (exit_status);
}

/*
frees 't_param' and returns 'exit_status'
*/
int	cleanup(int exit_status)
{
	free_info();
	return (exit_status);
}
