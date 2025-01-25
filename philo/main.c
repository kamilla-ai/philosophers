/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:44:50 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/16 19:44:23 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program	shared_data;

	if (checkargs(ac, av) != 0)
		return (1);
	if (create_table(av, &shared_data) != 0)
		return (1);
	if (create_philos(&shared_data) != 0)
		return (1);
	if (shared_data.num == 1)
	{
		if (one_philo(&shared_data) != 0)
			return (1);
	}
	else
	{
		if (more_philos(&shared_data) != 0)
			return (1);
	}
	return (0);
}
