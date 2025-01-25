/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:56:35 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/18 22:22:22 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_program *shared_data, int i)
{
	if (shared_data->num == 1)
		philo->first_fork = &shared_data->forks[i];
	else
	{
		if (philo->id % 2 == 0)
		{
			philo->first_fork = &shared_data->forks[i];
			philo->second_fork = &shared_data->forks[(i + 1)
				% shared_data->num];
		}
		else
		{
			philo->first_fork = &shared_data->forks[(i + 1) % shared_data->num];
			philo->second_fork = &shared_data->forks[i];
		}
	}
}

int	create_philos(t_program *shared_data)
{
	int	i;

	i = 0;
	shared_data->philos = malloc(sizeof(t_philo) * shared_data->num);
	if (!shared_data->philos)
	{
		free(shared_data->forks);
		return (1);
	}
	while (i < shared_data->num)
	{
		shared_data->philos[i].data = shared_data;
		shared_data->philos[i].id = i + 1;
		shared_data->philos[i].last_mealtime = get_timestamp();
		if (shared_data->philos[i].last_mealtime == -1)
		{
			free(shared_data->forks);
			free(shared_data->philos);
			return (1);
		}
		shared_data->philos[i].nbr_meals = 0;
		assign_forks(&shared_data->philos[i], shared_data, i);
		i++;
	}
	return (0);
}
