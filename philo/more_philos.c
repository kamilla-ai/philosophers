/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:50:37 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/21 12:19:43 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	if (philo->data->num % 2 != 0
		&& (philo->data->time_to_eat <= philo->data->time_to_sleep))
		philo_usleep(philo->data, (philo->data->time_to_eat * 2
				- philo->data->time_to_sleep) * 1000);
}

static void	updatefullnum(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->data->num_full++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_mealtime = get_timestamp();
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	write_status(philo->data->starttime, philo, "is eating");
	philo_usleep(philo->data, philo->data->time_to_eat * 1000);
	if (philo->nbr_meals == philo->data->max_meals)
		updatefullnum(philo);
}

static void	*more_algorithm(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	while (philo->nbr_meals != philo->data->max_meals
		&& !int_getter(&philo->data->end_mutex, &philo->data->end_simulation))
	{
		pthread_mutex_lock(&philo->first_fork->fork_mutex);
		write_status(philo->data->starttime, philo, "has taken a fork");
		philo->first_fork->value = 1;
		pthread_mutex_lock(&philo->second_fork->fork_mutex);
		write_status(philo->data->starttime, philo, "has taken a fork");
		philo->second_fork->value = 1;
		eating(philo);
		philo->second_fork->value = 0;
		pthread_mutex_unlock(&philo->second_fork->fork_mutex);
		philo->first_fork->value = 0;
		pthread_mutex_unlock(&philo->first_fork->fork_mutex);
		write_status(philo->data->starttime, philo, "is sleeping");
		philo_usleep(philo->data, philo->data->time_to_sleep * 1000);
		write_status(philo->data->starttime, philo, "is thinking");
		thinking(philo);
	}
	return (NULL);
}

int	more_philos(t_program *shared_data)
{
	int	i;

	i = 0;
	shared_data->starttime = get_timestamp();
	while (i < shared_data->num)
	{
		if (pthread_create(&shared_data->philos[i].philo_thread, NULL,
				more_algorithm, &shared_data->philos[i]) != 0)
		{
			free(shared_data->forks);
			free(shared_data->philos);
			return (1);
		}
		i++;
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
