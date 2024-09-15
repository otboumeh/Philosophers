/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:04:34 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/15 12:53:37 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long elapsed;
	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return;
	mutex_handler(&philo->table->write_mutex, LOCK);
	/* if (debug)
		write_status_debug(status, philo, elapsed); */
	/* else
	{ */
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
		printf(W"%-6ld"RESET" %d has taken a fork \n",elapsed, philo->id);
	else if ((status == EATING ) && !simulation_finished(philo->table))
		printf(W"%-6ld"RESET" %d is eating \n",elapsed, philo->id);
	else if ((status == SLEEPING ) && !simulation_finished(philo->table))
		printf(W"%-6ld"RESET" %d is sleeping \n",elapsed, philo->id);
	else if ((status == THINKING ) && !simulation_finished(philo->table))
		printf(W"%-6ld"RESET" %d s thinking \n",elapsed, philo->id);
	else if ((status == DIED ))
		printf(W"%-6ld"RESET" %d died \n",elapsed, philo->id);
	/* } */
	mutex_handler(&philo->table->write_mutex, UNLOCK);
}
