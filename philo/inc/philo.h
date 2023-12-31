/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:00:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 13:40:36 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>			// printf
# include <stdlib.h>		// malloc, free
# include <unistd.h>		// write, usleep
# include <sys/time.h>		// gettimeofday
# include <pthread.h>		// threads functions

# define TRUE		1
# define FALSE		0

# define SUCCESS	0
# define FAILURE	1

# ifndef INT_MAX
#  define INT_MAX	2147483647
# endif

# define PHILO_MAX	200

# define ERR_ARGC			"wrong number of arguments, expected 4 or 5"
# define ERR_ARG_INT		"arguments must be positive integers"
# define ERR_PHILO_MAX		"number of philosophers must be between 1 and 200"
# define ERR_TIMEOFDAY		"gettimeofday() failed"
# define ERR_MALLOC			"malloc() failed"
# define ERR_MUTEX_INIT		"pthread_mutex_init() failed"
# define ERR_MUTEX_DESTROY	"pthread_mutex_destroy() failed"
# define ERR_THREAD_CREATE	"pthread_create() failed"
# define ERR_THREAD_JOIN	"pthread_join() failed"

# define LOG_FORK			"has taken a fork"
# define LOG_EAT			"is eating"
# define LOG_SLEEP			"is sleeping"
# define LOG_THINK			"is thinking"
# define LOG_DIED			"died"
# define LOG_FULL			"is full"

# define RED				"\033[91m"
# define GREEN				"\033[92m"
# define YELLOW				"\033[93m"
# define ORANGE				"\033[38;5;208m"
# define BLUE				"\033[34m"
# define MAGENTA			"\033[95m"
# define CYAN				"\033[96m"
# define RESET				"\033[0m"

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
	int				meals_eaten;
	int				is_full;
	pthread_t		thread;
}					t_philo;

typedef struct s_info
{
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_goal;
	int				hungry_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	int				mutex_flag;
	t_philo			*philo_ptr;
	int				dead_philo;
	long			start_time;
	long			time_of_death;
	char			*error_msg;
}					t_info;

// arguments.c
int		args_are_valid(int argc, char **argv, char **reason);

// death.c
int		no_one_is_dead(t_info *info);
void	*check_for_dead(void *arg);

// error.c
void	set_error_msg(char *msg);
char	*get_error_msg(void);
void	put_error_msg(void);
int		error(int return_value);

// info.c
t_info	*call_info(void);
void	set_info(int argc, char **argv);
void	free_info(void);
int		cleanup(int exit_status);

// log.c
void	log_state_change(long time, int id, char *state, char *color);
void	log_death(long time_of_death, int id);
void	log_misc(char *msg, int time_flag);

// mutexes.c
int		setup_mutexes(void);
int		destroy_mutexes(void);
// void	lock_mutex(pthread_mutex_t *mutex, char *str, ...);

// philo.c
int		setup_philos(t_philo **philos);

// routine.c
void	*routine(void *arg);

// threads.c
int		create_threads(t_philo *philo_ptr, pthread_t *monitor);
int		wait_for_threads(t_philo *philo_ptr, pthread_t *monitor);

// time_utils.c
long	timeval_diff(struct timeval start, struct timeval end);
void	spend_time(long milliseconds);
long	philo_time(void);
// void	test_sleep_accuracy(void);

// utils.c
int		ft_isdigit(char c);
long	ft_atol(char *str);
void	ft_putstr_fd(char *str, int fd);

#endif
