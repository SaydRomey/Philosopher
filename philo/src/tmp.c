/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:31:18 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/29 12:26:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(void)
{
	t_info	*info;

	info = call_info();
	printf("\n");
	printf("philo count:\t%d\n", info->number_of_philos);
	printf("time to die:\t%ld\n", info->time_to_die);
	printf("time to eat:\t%ld\n", info->time_to_eat);
	printf("time to sleep:\t%ld\n", info->time_to_sleep);
	printf("meal goal:\t%d\n", info->meal_goal);
	printf("meal count:\t%d\n", info->total_meal_count);
	printf("\n");
}

/*
tmp function to test
*/
void	print_philo_info(t_philo *philo)
{
	int	i;

	i = 0;
	printf("\n");
	while (i < call_info()->number_of_philos)
	{
		printf("philo id:\t%d\n", philo[i].id);
		printf("philo index:\t%d\n", i);
		printf("lfork index:\t%d\n", philo[i].left_fork);
		printf("rfork index:\t%d\n", philo[i].right_fork);
		printf("last meal time:\t%ld\n", philo[i].last_meal_time);
		// printf("meals eaten:\t%d\n", philo[i].meals_eaten);
		printf("\n");
		i++;
	}
}

void	proof(char *msg)
{
	printf("%s\n", msg);
}
