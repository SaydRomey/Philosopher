/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/21 17:04:44 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define THREAD_NUM 8

pthread_mutex_t	mutex_fuel;
int				fuel = 50;

pthread_mutex_t mutex_water;
int				water = 10;

void	*routine(void *args)
{
	(void)args;
	pthread_mutex_lock(&mutex_fuel);
	pthread_mutex_lock(&mutex_water);
	fuel += 50;
	water = fuel;
	printf("Incremented fuel to %d\n", fuel);
	printf("Set water to %d\n", water);
	pthread_mutex_unlock(&mutex_fuel);
	pthread_mutex_unlock(&mutex_water);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	threads[THREAD_NUM];
	int			i;

	(void)argc;
	(void)argv;
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_mutex_init(&mutex_water, NULL);
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			return (printf("Error creating thread\n"), EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < THREAD_NUM)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("Error joining thread\n"), EXIT_FAILURE);
		i++;
	}
	printf("Fuel: %d\n", fuel);
	printf("Water: %d\n", water);
	pthread_mutex_destroy(&mutex_fuel);
	pthread_mutex_destroy(&mutex_water);
	return (EXIT_SUCCESS);
}
