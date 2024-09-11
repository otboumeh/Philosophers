/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:27:34 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/09 11:40:14 by otboumeh         ###   ########.fr       */
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

static void	thread_handler_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (status == EAGAIN)
		error_exit("No ressource to creat another thread");
	else if(status == EDEADLK)
		error_exit("dead lock detected");
	else if(status == EINVAL && opcode == CREATE)
		error_exit("th value specified by attr is invalid");
	else if(status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("tHE VALUE SPECIFIED BY THREAD IS NOT JOINABLE");
	else if (status == EPERM)
		error_exit("The caller does not have permission");
	else if (status == ESRCH)
		error_exit("no thread could be found corresponding to that");	
}

void	thread_handler(pthread_t *thread, void*(*foo)(void*), void *data,t_opcode opcode)
{
	if(opcode == CREATE)
		thread_handler_error(pthread_create(thread, NULL, foo, data), opcode);
	else if(opcode == JOIN)
		thread_handler_error(pthread_join(*thread, NULL), opcode);
	else if(opcode == DETACH)
		thread_handler_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for the thread handler");
}


