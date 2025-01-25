/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:46:37 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/16 16:03:21 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_algorithm(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	philo->first_fork->value = 1;
	write_status(philo->data->starttime, philo, "has taken a fork");
	while (!int_getter(&philo->data->end_mutex, &philo->data->end_simulation))
		usleep(100);
	philo->first_fork->value = 0;
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	return (NULL);
}

int	one_philo(t_program *shared_data)
{
	shared_data->starttime = get_timestamp();
	if (shared_data->starttime == -1)
	{
		free(shared_data->forks);
		free(shared_data->philos);
		return (1);
	}
	if (pthread_create(&shared_data->philos[0].philo_thread, NULL,
			one_algorithm, &shared_data->philos[0]) != 0)
	{
		free(shared_data->forks);
		free(shared_data->philos);
		return (1);
	}
	if (pthread_create(&shared_data->monitor, NULL, monitor, shared_data) != 0)
	{
		free(shared_data->forks);
		free(shared_data->philos);
		return (1);
	}
	clean(shared_data);
	return (0);
}
