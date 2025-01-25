/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:09:16 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/21 12:20:00 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_program *shared_data)
{
	int	i;

	i = 0;
	pthread_join(shared_data->monitor, NULL);
	while (i < shared_data->num)
	{
		pthread_join(shared_data->philos[i].philo_thread, NULL);
		i++;
	}
	i = 0;
	pthread_mutex_destroy(&shared_data->write_mutex);
	pthread_mutex_destroy(&shared_data->end_mutex);
	pthread_mutex_destroy(&shared_data->meal_mutex);
	while (i < shared_data->num)
	{
		pthread_mutex_destroy(&shared_data->forks[i].fork_mutex);
		i++;
	}
	free(shared_data->philos);
	free(shared_data->forks);
}
