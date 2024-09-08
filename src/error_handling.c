/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:27:34 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/08 13:06:54 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *malloc_creation(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with the allocation of memory");
	
	return(ret);
}
static void	mutex_handler_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && (opcode == INIT || opcode == DESTROY))
		error_exit("The value specified by attr is invalid");
	else if(status == EDEADLK)
		error_exit("");
	else if(status == ENOMEM)
		error_exit("Insufficient memory exists to initialize the mutex.");
	else if(status == EAGAIN)
		error_exit("lacked the necessary resources to initialize another mutex.");
	else if (status == EPERM)
		error_exit("The caller does not have the privilege to perform operation.");
	else if (status == EBUSY)
		error_exit("Mutex is locked");	
}

void	mutex_handler(t_mtx *mutex, t_opcode opcode)
{
	if(opcode == LOCK)
		mutex_handler_error(pthread_mutex_lock(mutex), opcode);
	else if(opcode == UNLOCK)
		mutex_handler_error(pthread_mutex_unlock(mutex), opcode);
	else if(opcode == INIT)
		mutex_handler_error(pthread_mutex_init(mutex, NULL), opcode);
	else if(opcode == DESTROY)
		mutex_handler_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for the MUTEX handler");
}
