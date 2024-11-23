/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:08:40 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/18 12:39:53 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* Changing the parsing format from string to
 num and verificating for every wriong caracter */
static t_data	parse_input(char **argv)
{
	t_data	data;

	data.philo_num = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.meal_nbr = ft_atoi(argv[5]) - (!argv[5]);
	data.finish = 0;
	data.id = 1;
	if (data.philo_num == -2 || data.philo_num == 0 || data.time_to_die == -2)
		return (printf("Input error\n"), exit(1), data);
	if (data.time_to_eat == -2 \
	|| data.time_to_sleep == -2 || data.meal_nbr == -2)
		return (printf("Input error\n"), exit(1), data);
	return (data);
}

/* fonction for alocating memory 
for every philosopher*/
static t_data	malloc_data(t_data data, int i)
{
	data.status = (int *)malloc(sizeof(int) * (data.philo_num + 1));
	if (!data.status)
		return (printf("Memory error\n"), exit(1), data);
	i = -1;
	while (++i <= data.philo_num)
		data.status[i] = 1;
	data.forks = (int *)malloc(sizeof(int) * (data.philo_num + 1));
	if (!data.forks)
	{
		printf("Memory error\n");
		return (free(data.forks), exit(1), data);
	}
	i = -1;
	while (++i <= data.philo_num)
		data.forks[i] = 1;
	data.fork_lock = malloc(sizeof(pthread_mutex_t) * (data.philo_num + 1));
	if (!data.fork_lock)
	{
		printf("Memory error\n");
		return (free(data.forks), free(data.fork_lock), exit(1), data);
	}
	i = -1;
	while (++i <= data.philo_num)
		pthread_mutex_init(&data.fork_lock[i], NULL);
	return (data);
}
/* initilization of mutexes (LOcks)
 */

static t_data	start_mutex(t_data data)
{
	pthread_mutex_init(&data.id_setting, NULL);
	pthread_mutex_init(&data.time, NULL);
	pthread_mutex_init(&data.stat_lock, NULL);
	pthread_mutex_init(&data.mutexes, NULL);
	pthread_mutex_init(&data.edit_fork, NULL);
	return (data);
}
/* Creation of threads
 */

static int	create_threads(t_data *data)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * (data->philo_num + 1));
	i = -1;
	while (++i < data->philo_num)
	{
		threads[i] = i + 1;
		if (pthread_create(&threads[i], NULL, philo, data))
			return (printf("Error\n"), 1);
	}
	threads[i] = i + 1;
	if (pthread_create(&threads[i], NULL, threads_manage, data))
		return (printf("Error\n"), 1);
	i = -1;
	while (++i <= data->philo_num)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_lock(&data->mutexes);
		data->finish ++;
		pthread_mutex_unlock(&data->mutexes);
	}
	return (free(threads), 0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (argc < 5 || 6 < argc)
		return (printf("Wrong number of arguments\n"), 1);
	data = parse_input(argv);
	data = malloc_data(data, 0);
	data = start_mutex(data);
	my_time(SET, &data);
	create_threads(&data);
	pthread_mutex_destroy(&data.id_setting);
	pthread_mutex_destroy(&data.time);
	pthread_mutex_destroy(&data.stat_lock);
	pthread_mutex_destroy(&data.mutexes);
	pthread_mutex_destroy(&data.edit_fork);
	i = -1;
	while (++i <= data.philo_num)
		pthread_mutex_destroy(&data.fork_lock[i]);
	free(data.fork_lock);
	free(data.forks);
	free(data.status);
	return (0);
}
