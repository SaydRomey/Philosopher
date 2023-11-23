/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:05:12 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/22 23:38:33 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo *philos;

	if (args_are_valid(argc, argv))
		set_params(argc, argv);
	else
		return (error(EXIT_FAILURE));
	// 
	if (setup_philos(&philos) == EXIT_FAILURE)
		return (error(EXIT_FAILURE));
	// 
	return (cleanup(EXIT_SUCCESS));
}
