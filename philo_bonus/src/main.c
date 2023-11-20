/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:29:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/20 16:43:32 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	x;
	int	pid;

	(void)argc;
	(void)argv;
	// 
	x = 2;
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		x++;
	sleep(2);
	printf("Value of x: %d\n", x);
	if (pid != 0)
		wait(NULL);
	// 
	return (0);
}