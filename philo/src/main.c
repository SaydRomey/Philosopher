/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/09 22:46:39 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		start_simulation(void);
static int	cancel_dinner(char *reason);

int	main(int argc, char **argv)
{
	int		ok;
	char	*reason;
	t_philo	*philo;

	ok = TRUE;
	reason = NULL;
	if (args_are_valid(argc, argv, &reason) != TRUE)
		return (cancel_dinner(reason));
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

static int	table_for_one(void)
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
	if (create_threads(philo, &monitor) != SUCCESS)
		return (put_error_msg());
	if (wait_for_threads(philo, &monitor) != SUCCESS)
		return (put_error_msg());
}

static int	cancel_dinner(char *reason)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(reason, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FAILURE);
}
