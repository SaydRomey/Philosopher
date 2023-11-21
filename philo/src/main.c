/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/20 21:45:32 by cdumais          ###   ########.fr       */
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
	pthread_t	thread[4];
	int			i;

	(void)argc;
	(void)argv;
	// 
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, &routine, NULL) != 0)
		{
			perror("pthread_create");
			return (1);
		}
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (2);
		printf("Thread %d has ended\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Value of x: %d\n", x);
	// 
	return (0);
}
