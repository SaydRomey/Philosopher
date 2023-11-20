/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/20 15:39:23 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;
	printf("routine from thread\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t thread;

	(void)argc;
	(void)argv;
	pthread_create(&thread, NULL, &routine, NULL);
	pthread_join(thread, NULL);
	return (0);
}
