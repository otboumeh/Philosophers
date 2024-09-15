/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:25:55 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/14 20:07:46 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	assign_forks(t_philo *philo,t_fork *forks, int philo_position)
{
	int philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	
}

static void philo_init(t_table *table)
{
	int i;
	t_philo *philo;

	i = -1;
	while (i++ < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->nbr_meals = 0;
		philo->table = table;
	}
	assign_forks(philo, table->forks, i);
}

void	data_init(t_table *table)
{	
	int i;
	
	i = -1;
	table->end_simulation = false;
	table->threads_ready = false;
	table->philos = malloc_creation(sizeof(t_philo) * table->philo_nbr);
	mutex_handler(&table->table_mutex, INIT);
	mutex_handler(&table->write_mutex, INIT);
	table->forks = malloc_creation(sizeof(t_fork) * table->philo_nbr);
	while (i++ < table->philo_nbr)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}