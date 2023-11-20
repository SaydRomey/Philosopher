/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:25:17 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/20 16:27:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
*/

# include <string.h> // memset
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // write, fork, usleep
# include <sys/time.h> // gettimeofday
# include <sys/wait.h> // waitpid
# include <signal.h> // kill
# include <pthread.h> // pthread_create, pthread_detach, pthread_join
# include <semaphore.h> // sem_open, sem_close, sem_post, sem_wait, sem_unlink

#endif
