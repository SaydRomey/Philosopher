/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:00:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/23 10:31:31 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> // memset
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // threads functions


# define TRUE	1
# define FALSE	0

# define PHILO_MAX	200

# define ERR_ARGC		"wrong number of arguments, expected 4 or 5"
# define ERR_ARG_INT	"arguments must be positive integers"
# define ERR_PHILO_MAX	"number of philosophers must be between 1 and 200"
# define ERR_TIMEOFDAY	"gettimeofday() failed"

// state change messages
# define LOG_FORK	"has taken a fork"
# define LOG_EAT	"is eating"
# define LOG_SLEEP	"is sleeping"
# define LOG_THINK	"is thinking"
# define LOG_DIED	"died"

typedef struct s_param
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	int				dead_philo;
	char			*error_msg;
	pthread_mutex_t	log_msg;
	struct timeval	start_time;
}			t_param;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork; //pointer to next philo's left fork
	struct timeval	last_meal; // time of last meal
	int				meal_count;
}					t_philo;

// arguments.c
int		args_are_valid(int argc, char **argv);

// params.c
t_param	*call_param(void);
void	set_params(int argc, char **argv);
void	set_error_msg(char *msg);
char	*get_error_msg(void);
void	free_param(void);

// philo.c
int		setup_philos(t_philo **philos);

// sleep.c
long	timeval_diff(struct timeval start, struct timeval end);
void	spend_time(long milliseconds);
void	test_sleep_accuracy(void);

// utils.c
int		ft_isdigit(char c);
int		ft_atoi(char *str);
void	ft_putstr_fd(char *str, int fd);
int		error(int exit_status);
int		cleanup(int exit_status);

#endif
