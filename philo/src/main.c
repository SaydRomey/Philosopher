/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/20 20:48:42 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	x = 0;
pthread_mutex_t mutex;

void	*routine(void *arg)
{
	int	i;

	(void)arg;
	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&mutex);
		x++;
		i++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t thread_1;
	pthread_t thread_2;

	(void)argc;
	(void)argv;
	// 
	pthread_mutex_init(&mutex, NULL);
	// 
	if (pthread_create(&thread_1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&thread_2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(thread_1, NULL) != 0)
		return (3);
	if (pthread_join(thread_2, NULL) != 0)
		return (4);
	printf("Value of x: %d\n", x);
	// 
	pthread_mutex_destroy(&mutex);
	// 
	return (0);
}
