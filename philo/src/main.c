/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/21 16:18:14 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*thread_func(void *arg)
{
	int	index;
	int	sum;
	int	i;

	index = *(int *)arg;
	sum = 0;
	i = 0;
	while (i < 5)
	{
		sum += primes[index + i];
		i++;
	}
	printf("local sum = %d\n", sum);
	*(int *)arg = sum;
	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t	thread[2];
	int			i;
	int			*a;
	int			*r;
	int			sum = 0;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&thread[i], NULL, &thread_func, a) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (pthread_join(thread[i], (void **)&r) != 0)
			return (1);
		sum += *r;
		i++;
	}
	free(r);
	printf("global sum = %d\n", sum);
	return (0);
}
