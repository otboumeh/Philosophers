/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:13:18 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/07 19:19:57 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		error_exit("Invalid arguments number");
	parse_input(&table, argc, argv);
	/* data_init(&table);
	diner_start(&table); */
	/* clean(&table);	 */
}