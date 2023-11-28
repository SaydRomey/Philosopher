/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/28 14:04:35 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_philo *philo)
{
	printf("Starting simulation...\n");
	free(philo);
}

int	main(int argc, char **argv)
{
	t_philo *philo;
	int		ok;

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
		start_simulation(philo);
	else
		return (error(FAILURE));
	return (cleanup(SUCCESS));
}
