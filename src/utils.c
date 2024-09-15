/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:45:10 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/14 20:03:03 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_exit(const char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(EXIT_FAILURE);
}

long	gettime(t_time_code time_code)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL))
		error_exit("Gettime of day failed");
	if (SECOND == time_code)
		return(tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime ");
	return(0);
}

void modified_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else 
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}	
}