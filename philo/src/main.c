/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/21 11:14:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

void	*roll_dice(void *arg)
{
	int	value;
	int	*result;
	
	(void)arg;
	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	*result = value;
	printf("Thread result: %p\n", result);
	return ((void *)result);
}

int	main(int argc, char **argv)
{
	pthread_t	thread;
	int			*res;

	(void)argc;
	(void)argv;
	srand(time(NULL));
	if (pthread_create(&thread, NULL, roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(thread, (void **)&res) != 0)
		return (1);
	printf("Main res: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	return (0);
}
