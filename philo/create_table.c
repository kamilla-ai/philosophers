/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:22:26 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/21 12:20:23 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_mutexes(t_program *shared_data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&shared_data->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&shared_data->end_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&shared_data->meal_mutex, NULL) != 0)
		return (1);
	while (i < shared_data->num)
	{
		if (pthread_mutex_init(&shared_data->forks[i].fork_mutex, NULL) != 0)
			return (1);
		shared_data->forks[i].id = i;
		shared_data->forks[i].value = 0;
		i++;
	}
	return (0);
}

int	create_table(char **av, t_program *shared_data)
{
	shared_data->num = ph_atoi(av[1]);
	shared_data->time_to_die = (long)ph_atoi(av[2]);
	shared_data->time_to_eat = (long)ph_atoi(av[3]);
	shared_data->time_to_sleep = (long)ph_atoi(av[4]);
	if (shared_data->num <= 0 || shared_data->time_to_die < 60
		|| shared_data->time_to_eat < 60 || shared_data->time_to_sleep < 60)
		return (1);
	shared_data->max_meals = -1;
	if (av[5] && ph_atoi(av[5]) <= 0)
		return (1);
	else if (av[5])
		shared_data->max_meals = ph_atoi(av[5]);
	shared_data->forks = malloc(sizeof(t_fork) * shared_data->num);
	if (!shared_data->forks)
		return (1);
	if (create_mutexes(shared_data) != 0)
	{
		free(shared_data->forks);
		return (1);
	}
	shared_data->end_simulation = 0;
	shared_data->num_full = 0;
	return (0);
}
