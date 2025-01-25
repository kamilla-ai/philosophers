/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:52:24 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/17 19:27:07 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	alive(t_philo *philo, long time)
{
	long	diff;

	diff = time - long_getter(&philo->data->meal_mutex, &philo->last_mealtime);
	if (int_getter(&philo->data->meal_mutex,
			&philo->nbr_meals) != philo->data->max_meals
		&& diff > philo->data->time_to_die)
	{
		return (false);
	}
	return (true);
}

static void	write_death(long starttime, t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	printf("%ld %d %s\n", get_timestamp() - starttime, philo->id, status);
	pthread_mutex_unlock(&philo->data->write_mutex);
}

static int	checkmeals(t_program *shared_data)
{
	if (int_getter(&shared_data->meal_mutex,
			&shared_data->num_full) == shared_data->num)
	{
		pthread_mutex_lock(&shared_data->end_mutex);
		shared_data->end_simulation = 1;
		pthread_mutex_unlock(&shared_data->end_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_program	*shared_data;
	int			i;

	shared_data = (t_program *)arg;
	while (!shared_data->end_simulation)
	{
		i = 0;
		while (i < shared_data->num && !shared_data->end_simulation)
		{
			if (!alive(&shared_data->philos[i], get_timestamp()))
			{
				pthread_mutex_lock(&shared_data->end_mutex);
				shared_data->end_simulation = 1;
				pthread_mutex_unlock(&shared_data->end_mutex);
				write_death(shared_data->starttime, &shared_data->philos[i],
					"died");
				return (NULL);
			}
			if (checkmeals(shared_data) == 1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
