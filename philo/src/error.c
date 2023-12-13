/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:45:48 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 13:40:41 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_error_msg(char *msg)
{
	t_info	*info;

	info = call_info();
	if (info->error_msg)
		free(info->error_msg);
	info->error_msg = msg;
}

char	*get_error_msg(void)
{
	t_info	*info;

	info = call_info();
	if (!info->error_msg)
		return ("[error message not set]");
	return (info->error_msg);
}

void	put_error_msg(void)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(get_error_msg(), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	error(int return_value)
{
	put_error_msg();
	free_info();
	return (return_value);
}
