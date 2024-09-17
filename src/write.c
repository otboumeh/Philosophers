/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:04:34 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/17 11:35:07 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
	printf("%-6ld %d has taken the first fork""\t\t\t  %d\n",elapsed,philo->id,philo->first_fork->fork_id);
else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
	printf("%-6ld  %d has taken the second fork""\t\t\t  %d\n",elapsed,philo->id,philo->second_fork->fork_id);
else if (status == EATING && !simulation_finished(philo->table))
	printf("%-6ld  %d is eating\t\t\t  %ld\n",elapsed,philo->id,philo->nbr_meals);
else if (status == SLEEPING && !simulation_finished(philo->table))
	printf("%-6ld %d is sleeping",elapsed, philo->id);
else if (status == THINKING && !simulation_finished(philo->table))
	printf("%-6ld %d is thinking",elapsed, philo->id);
else if (status == DIED)
	printf("%-6ld %d DIED",elapsed, philo->id);	
}

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed;
	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return;
	mutex_handler(&philo->table->write_mutex, LOCK);
	 if (debug)
		write_status_debug(status, philo, elapsed);
	 else
	{
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
		printf("%-6ld%d has taken a fork \n",elapsed, philo->id);
	else if ((status == EATING ) && !simulation_finished(philo->table))
		printf("%-6ld%d is eating \n",elapsed, philo->id);
	else if ((status == SLEEPING ) && !simulation_finished(philo->table))
		printf("%-6ld %d is sleeping \n",elapsed, philo->id);
	else if ((status == THINKING ) && !simulation_finished(philo->table))
		printf("%-6ld%d s thinking \n",elapsed, philo->id);
	else if ((status == DIED ))
		printf("%-6ld %d died \n",elapsed, philo->id);
	}
	mutex_handler(&philo->table->write_mutex, UNLOCK);
}
