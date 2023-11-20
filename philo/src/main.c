/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/20 16:46:21 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	x = 2;

void	*routine(void *arg)
{
	(void)arg;
	x += 5;
	sleep(2);
	printf("Value of x: %d\n", x);
	return (NULL);
}

void	*routine2(void *arg)
{
	(void)arg;
	sleep(2);
	printf("Value of x: %d\n", x);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t thread_1;
	pthread_t thread_2;

	(void)argc;
	(void)argv;
	// 
	if (pthread_create(&thread_1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&thread_2, NULL, &routine2, NULL) != 0)
		return (2);
	if (pthread_join(thread_1, NULL) != 0)
		return (3);
	if (pthread_join(thread_2, NULL) != 0)
		return (4);
	// 
	return (0);
}
