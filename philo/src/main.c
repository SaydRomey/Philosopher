/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/04 14:20:08 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	table_for_one(void)
{
	t_info	*info;

	info = call_info();
	if (info->number_of_philos == 1)
	{
		printf("0\t1 %s\n", LOG_FORK);
		spend_time(info->time_to_die);
		printf("%ld\t1 %s%s%s\n", info->time_to_die, RED, LOG_DIED, RESET);
		return (TRUE);
	}
	return (FALSE);
}

void	start_simulation(void)
{
	t_info		*info;
	t_philo		*philo;
	pthread_t	monitor;

	if (table_for_one())
		return ;
	info = call_info();
	philo = info->philo_ptr;
	info->start_time = philo_time();
	// 	
	if (pthread_create(&monitor, NULL, check_for_dead, philo) != SUCCESS)
		return (put_error_msg());
	// 
	if (create_threads(philo) != SUCCESS)
			return (put_error_msg());
	// 
	if (pthread_join(monitor, NULL) != SUCCESS)
		return (put_error_msg());
	// 
	if (wait_for_threads(philo) != SUCCESS)
			return (put_error_msg());
}

int	main(int argc, char **argv)
{
	int		ok;
	t_philo *philo;

	ok = TRUE;
	if (!args_are_valid(argc, argv))
		ok = FALSE;
	else
	{
		set_info(argc, argv);
		if (setup_philos(&philo) != SUCCESS)
			ok = FALSE;
		else if (setup_mutexes() != SUCCESS)
			ok = FALSE;
	}
	if (ok)
		start_simulation();
	else
		return (error(FAILURE));
	return (cleanup(SUCCESS));
}
