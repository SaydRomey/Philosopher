/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 12:43:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo *philos;

	if (args_are_valid(argc, argv))
		set_info(argc, argv);
	else
		return (error(EXIT_FAILURE));
	// 
	if (setup_philos(&philos) == EXIT_FAILURE)
		return (error(EXIT_FAILURE));
	// 
	return (cleanup(EXIT_SUCCESS));
}
