/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:45:48 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 12:09:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
sets the error message in t_info
and returns FALSE (0)
*/
void	set_error_msg(char *msg)
{
	t_info	*info;

	info = call_info();
	if (info->error_msg)
		free(info->error_msg);
	info->error_msg = msg;
}

/*
returns current error message in 't_info'
*/
char	*get_error_msg(void)
{
	t_info	*info;

	info = call_info();
	return (info->error_msg);
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
