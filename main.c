/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshiki <tshiki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:13:18 by otboumeh          #+#    #+#             */
/*   Updated: 2024/09/17 11:38:46 by tshiki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		error_exit("Invalid arguments number");
	parse_input(&table, argc, argv);
	data_init(&table);
	dinner_start(&table);
	/* clean(&table);	 */
}