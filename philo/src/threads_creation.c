/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:08:42 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/18 12:45:43 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long int	dinner_time(int id, t_data *data, long int last_meal)
{
	wait_fork(id, data, last_meal);
	take_fork(id, id, data);
	if (data->philo_num == 1)
		return (modified_usleep(data->time_to_die + 1, data, last_meal, id), 0);
	wait_fork((id % data->philo_num) + 1, data, last_meal);
	take_fork(id, (id % data->philo_num) + 1, data);
	last_meal = eating(id, data, last_meal);
	leave_fork(id, data);
	leave_fork((id % data->philo_num) + 1, data);
	return (last_meal);
}

static int	finish(int id, t_data *data)
{
	pthread_mutex_lock(&data->stat_lock);
	pthread_mutex_lock(&data->mutexes);
	if (data->status[id] == 0)
	{
		pthread_mutex_unlock(&data->stat_lock);
		pthread_mutex_unlock(&data->mutexes);
		return (1);
	}
	pthread_mutex_unlock(&((t_data *)data)->mutexes);
	pthread_mutex_unlock(&((t_data *)data)->stat_lock);
	return (0);
}

static int	init_philo(t_data *data)
{
	int	id;

	pthread_mutex_lock(&((t_data *)data)->id_setting);
	id = ((t_data *)data)->id;
	((t_data *)data)->id ++;
	pthread_mutex_unlock(&((t_data *)data)->id_setting);
	modified_usleep((((t_data *)data)->time_to_eat - 1) *!(id % 2), \
	data, 0, id);
	return (id);
}

void	*philo(void *data)
{
	int			id;
	int			eaten;
	long int	last_meal;

	id = init_philo(data);
	last_meal = 0;
	eaten = -1;
	while (++eaten != ((t_data *)data)->meal_nbr && !finish(id, data))
	{
		if (eaten > 0)
		{
			status(data, last_meal, id);
			printing_things(id, "is sleeping", data);
			modified_usleep(((t_data *)data)->time_to_sleep, \
			data, last_meal, id);
		}
		printing_things(id, "is thinking", data);
		last_meal = dinner_time(id, data, last_meal);
	}
	return (NULL);
}

/* fonction that manage and 
synchronize the threads (philos)  */
void	*threads_manage(void *data)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&((t_data *)data)->mutexes);
		if (((t_data *)data)->finish == ((t_data *)data)->philo_num)
			break ;
		i = 0;
		while (++i <= ((t_data *)data)->philo_num)
		{
			if (((t_data *)data)->status[i] == 0)
			{
				i = 0;
				while (++i <= ((t_data *)data)->philo_num)
					((t_data *)data)->status[i] = 0;
				break ;
			}
		}
		pthread_mutex_unlock(&((t_data *)data)->mutexes);
		usleep(5000);
	}
	pthread_mutex_unlock(&((t_data *)data)->mutexes);
	return (NULL);
}
