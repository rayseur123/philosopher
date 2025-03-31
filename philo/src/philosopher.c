/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:53:50 by njooris           #+#    #+#             */
/*   Updated: 2025/03/28 14:42:53 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parsing.h"
#include "dinner.h"

t_table	free_table(t_table table, int size_malloc)
{
	int	i;

	i = 0;
	while (i < size_malloc)
	{
		if (i == 0)
		{
			free(table.table[i].fork_left);
			free(table.table[i].fork_right);
		}
		else if (i != table.nb_chair - 1)
			free(table.table[i].fork_left);
		i++;
	}
	free(table.table);
	table.table = NULL;
	return (table);
}

void	philosopher(t_data data)
{
	t_table	table;

	table = set_the_table(data);
	if (!table.table)
	{
		printf("MALLOC ERROR\n");
		return ;
	}
}
