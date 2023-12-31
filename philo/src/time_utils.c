/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:09:59 by cdumais           #+#    #+#             */
/*   Updated: 2023/12/13 13:55:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
takes two timeval structs and returns the difference in microseconds
*/
long	timeval_diff(struct timeval start, struct timeval end)
{
	long	seconds;
	long	microseconds;
	long	elapsed;

	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed = seconds * 1000000;
	elapsed += microseconds;
	return (elapsed);
}

/*
precise implementation of a sleeping function
*/
void	spend_time(long milliseconds)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;
	long			remaining;
	long			microseconds;

	microseconds = milliseconds * 1000;
	gettimeofday(&start, NULL);
	elapsed = 0;
	while (TRUE)
	{
		gettimeofday(&current, NULL);
		elapsed = timeval_diff(start, current);
		remaining = microseconds - elapsed;
		if (elapsed >= microseconds)
			break ;
		if (remaining > 1000)
			usleep(remaining / 2);
	}
}

/*
get current time in milliseconds
*/
long	philo_time(void)
{
	struct timeval	time;
	long			milliseconds;

	if (gettimeofday(&time, NULL) == -1)
	{
		set_error_msg(ERR_TIMEOFDAY);
		return (-1);
	}
	milliseconds = (long)time.tv_sec * 1000;
	milliseconds += (long)time.tv_usec / 1000;
	return (milliseconds);
}

/*
// * (replace 'spend_time(TEST_TIME)' with your function to test its precision)
# define TEST_TIME 1000

void	test_sleep_accuracy(void)
{
	struct timeval	start;
	struct timeval	end;
	long			seconds;
	long			microseconds;
	double			elapsed_milliseconds;

	gettimeofday(&start, NULL);
	// 
	spend_time(TEST_TIME);
	// 
	gettimeofday(&end, NULL);
	// 
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	elapsed_milliseconds = (seconds * 1000) + (microseconds / 1000.0);
	// 
	printf("Expected sleep duration:\t%d ms\n", TEST_TIME);
	printf("Actual sleep duration:\t\t%.2f ms\n", elapsed_milliseconds);
}
*/
