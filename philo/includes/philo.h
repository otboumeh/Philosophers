/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:08:54 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/18 12:08:08 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define SET 0
# define GET 1

typedef struct s_data
{
	int				philo_num;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				meal_nbr;

	int				id;
	int				finish;

	int				*status;
	int				*forks;

	pthread_mutex_t	id_setting;
	pthread_mutex_t	time;
	pthread_mutex_t	stat_lock;
	pthread_mutex_t	mutexes;
	pthread_mutex_t	edit_fork;
	pthread_mutex_t	*fork_lock;
}	t_data;

//Thread
void		*threads_manage(void *data);
void		*philo(void *data);
//Actions
void		modified_usleep(long int ms, t_data *data, \
long int last_meal, int id);
void		wait_fork(int id, t_data *data, long int last_meal);
void		take_fork(int id, int fork_id, t_data *data);
void		leave_fork(int fork_id, t_data *data);
int			eating(int id, t_data *data, long int last_meal);
//Utils
void		printing_things(int id, char *line, t_data *data);
void		status(t_data *data, long int last_meal, int id);
long int	my_time(int check, t_data *data);
int			ft_atoi(char *line);

#endif
