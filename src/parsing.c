/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 17:19:14 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/08 10:59:27 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	inline	bool	ft_is_digit(const char c)
{
	return(c >= '0' && c <= '9');
}

static	inline	bool	ft_is_space(const char c)
{
	return((c >= 9 && c <= 13) || c == 32);
}

static	const char *valid_input(const char *str)
{
	int 		len;
	char const *nbr;

	len = 0;
	while(ft_is_space(*str))
		str++;
	if (*str == '+' )
		str++;
	else if (*str == '-')
		error_exit("Nice try hihi give me positif nbr");
	if (!ft_is_digit(*str))
			error_exit("Nice try hihi , give me only numbers");
	nbr = str;
	while(ft_is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("Nice try , The number is bigger than INT_MAX");
	return (nbr);
}

static	long	ft_atol(const char *str)
{
	long num;	
	int i;

	i = 0;
	num = 0;
	str = valid_input(str);
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			error_exit("Nice try hihi , give me only numbers");
		i++;
	}
	while (ft_is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("Nice try , The number is bigger than INT_MAX");
	return (num);
}


void	parse_input(t_table *table, int argc,  char **argv)
{
	table->philo_nbr = (ft_atol(argv[1]));
	table->time_to_die = (ft_atol(argv[2])) * 1000;
	table->time_to_eat = (ft_atol(argv[3])) * 1000;
	table->time_to_sleep = (ft_atol(argv[4])) * 1000;
	if (table->philo_nbr == 0)
		error_exit("Unvalid number of philos");
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
			error_exit("use time stamps bigger than 60ms");
	if (argc == 6)
	{
		table->nbr_limit_meals = (ft_atol(argv[5]));
		if (table->nbr_limit_meals == 0)
			error_exit("Unvalid meals number");
	}
	else
		table->nbr_limit_meals = -1;
}
