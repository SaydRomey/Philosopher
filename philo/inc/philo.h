/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:00:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/29 12:26:24 by cdumais          ###   ########.fr       */
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


# define TRUE		1
# define FALSE		0

# define SUCCESS	0
# define FAILURE	1

# ifndef INT_MAX
# 	define INT_MAX	2147483647
# endif

# define PHILO_MAX	200

// error messages

# define ERR_ARGC			"wrong number of arguments, expected 4 or 5"
# define ERR_ARG_INT		"arguments must be positive integers"
# define ERR_PHILO_MAX		"number of philosophers must be between 1 and 200"
# define ERR_TIMEOFDAY		"gettimeofday() failed"
# define ERR_MALLOC			"malloc() failed"
# define ERR_MUTEX_INIT		"pthread_mutex_init() failed"
# define ERR_MUTEX_DESTROY	"pthread_mutex_destroy() failed"
# define ERR_THREAD_CREATE	"pthread_create() failed"
# define ERR_THREAD_JOIN	"pthread_join() failed"

// log messages

# define LOG_FORK	"has taken a fork"
# define LOG_EAT	"is eating"
# define LOG_SLEEP	"is sleeping"
# define LOG_THINK	"is thinking"
# define LOG_DIED	"died"

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
	// int				meals_eaten;
	pthread_t		thread;
}					t_philo;

typedef struct s_info
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_goal; // optional (default = -1)
	int				total_meal_count;
	// 
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_msg;
	pthread_mutex_t	philo_state;
	pthread_mutex_t	meal_time;
	// 
	t_philo			*philo_ptr;
	int				dead_philo;
	long			start_time;
	char			*error_msg;
}					t_info;

// arguments.c
int		args_are_valid(int argc, char **argv);

// cleanup.c
int		cleanup(int exit_status);

// death.c
void	check_for_dead(t_philo *philo_ptr);

// error.c
void	set_error_msg(char *msg);
char	*get_error_msg(void);
void	put_error_msg(void);
int		error(int return_value);

// info.c
t_info	*call_info(void);
void	set_info(int argc, char **argv);
void	free_info(void);

// log.c
void	log_state_change(long time, int id, char *state);
void	log_death(long time, int id);

// mutexes.c
int		allocate_forks(void);
int		init_mutexes(void);
int		setup_mutexes(void);
int		destroy_mutexes(void);

// philo.c
int		setup_philos(t_philo **philos);

// routine.c
void	*routine(void *arg);

// threads.c
int		create_threads(t_philo *philo_ptr);
int		wait_for_threads(t_philo *philo_ptr);

// time_utils.c
long	timeval_diff(struct timeval start, struct timeval end);
void	spend_time(long milliseconds);
long	philo_time(void);
void	test_sleep_accuracy(void);

// tmp.c
void	print_info(void);
void	print_philo_info(t_philo *philo);
void	proof(char *msg);

// utils.c
int		ft_isdigit(char c);
long	ft_atol(char *str);
void	ft_putstr_fd(char *str, int fd);

#endif
