/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:24:13 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/17 11:38:48 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static void thinking(t_philo *philo)
{
	write_status(THINKING,philo, DEBUG_MODE);
}


static void eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK,philo, DEBUG_MODE);
	mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK,philo, DEBUG_MODE);

	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECOND));
	philo->nbr_meals++;
	write_status(EATING, philo, DEBUG_MODE);
	modified_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 && philo->nbr_meals == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);

}

void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finished)
	{
		if (philo->full)
			break;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		modified_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	
}

void	dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (table->nbr_limit_meals == 0)
			return;
	else if (table->philo_nbr = 1)
		;
	else
	{
		while (table->philo_nbr > i++)
		{
			thread_handler(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE);
		}
	}
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);	
	i = -1;
	while (table->philo_nbr > i++)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}