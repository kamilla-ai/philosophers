/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:15:15 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/16 21:27:21 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_usleep(t_program *shared_data, long usec)
{
	long	start_time;
	long	current_time;

	start_time = get_timestamp();
	current_time = start_time;
	while ((current_time - start_time) * 1000 < usec
		&& !int_getter(&shared_data->end_mutex, &shared_data->end_simulation))
	{
		usleep(100);
		current_time = get_timestamp();
	}
}

void	write_status(long starttime, t_philo *philo, char *status)
{
	if (!int_getter(&philo->data->end_mutex, &philo->data->end_simulation))
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		if (!int_getter(&philo->data->end_mutex, &philo->data->end_simulation))
		{
			printf("%ld %d %s\n", get_timestamp() - starttime, philo->id,
				status);
		}
		pthread_mutex_unlock(&philo->data->write_mutex);
	}
}

int	int_getter(pthread_mutex_t *mutex, int *value)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}

long	long_getter(pthread_mutex_t *mutex, long *value)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *value;
	pthread_mutex_unlock(mutex);
	return (res);
}
