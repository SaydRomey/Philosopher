/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:30:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 14:05:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
frees 't_param' and returns 'exit_status'
*/
int	cleanup(int exit_status)
{
	free_info();
	return (exit_status);
}
