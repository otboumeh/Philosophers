/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:24:13 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/13 12:41:40 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
}

void	dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (table->nbr_limit_meals == 0)
			return;
	else if (table->philo_nbr = 1)
		////;
	else
	{
		while (table->philo_nbr > i++)
		{
			thread_handler(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE);
		}
	}
	set_bool(&table->table_mutex, &table->threads_ready, true);	
}