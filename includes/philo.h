/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:07:56 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/16 12:25:51 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h> //printf
#include <unistd.h> // write , usleep
#include <stdlib.h> // malloc , free
#include <stdbool.h> // boolean
#include <pthread.h> // mutex: init destroy lock unlock
#include <sys/time.h> // gettimeofday
#include <limits.h> // INT_MAX INT_MIN
#include <errno.h> // Errors
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define Y "\033[33m"
#define B   "\033[34m"
#define MAGENTA "\033[35m"
#define W   "\033[37m"
#define RESET   "\033[0m"
#define DEBUG_MODE 0
// we will need 3 structs one for the philo, one for the fork and one for the elements(time ...)
typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;
typedef enum e_opcode
{	
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;	
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		nbr_meals;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mtx;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	bool	threads_ready;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

//utils.c
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	modified_usleep(long usec, t_table *table);


//parsing.c
void	parse_input(t_table *table,int argc, char **argv);

//error_handling.c
void	*malloc_creation(size_t bytes);
void	thread_handler(pthread_t *thread, void*(*foo)(void*), void *data,t_opcode opcode);
void	mutex_handler(t_mtx *mutex, t_opcode opcode);
// init.c
void	data_init(t_table *table);

//dinner.c
void	dinner_start(t_table *table);
void *dinner_simulation(void *data);


//getter_setters.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);

//synchro_util.c
void	wait_all_threads(t_table *table);

//write.c
void write_status(t_philo_status status, t_philo *philo, bool debug);



#endif
