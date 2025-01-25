/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:57:33 by krazikho          #+#    #+#             */
/*   Updated: 2024/10/21 12:20:43 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int					id;
	pthread_mutex_t		fork_mutex;
	int					value;
}						t_fork;

typedef struct s_program
{
	int					num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					max_meals;
	t_fork				*forks;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		end_mutex;
	pthread_mutex_t		meal_mutex;
	int					end_simulation;
	int					num_full;
	t_philo				*philos;
	long				starttime;
	pthread_t			monitor;
}						t_program;

typedef struct s_philo
{
	t_program			*data;
	int					id;
	long				last_mealtime;
	int					nbr_meals;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			philo_thread;
}						t_philo;

int						checkargs(int ac, char **av);
int						ph_atoi(const char *str);
int						create_table(char **av, t_program *shared_data);
int						create_philos(t_program *shared_data);
long					get_timestamp(void);
void					philo_usleep(t_program *shared_data, long usec);
int						more_philos(t_program *shared_data);
int						one_philo(t_program *shared_data);
void					*monitor(void *arg);
void					clean(t_program *shared_data);
void					write_status(long starttime, t_philo *philo,
							char *status);
long					long_getter(pthread_mutex_t *mutex, long *value);
int						int_getter(pthread_mutex_t *mutex, int *value);

#endif