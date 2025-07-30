/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:37:23 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 09:31:17 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dinner.h"

t_fork	*set_fork(void)
{
	t_fork	*fork1;

	fork1 = malloc(sizeof(t_fork));
	if (!fork1)
		return (NULL);
	fork1->fork = 0;
	if (pthread_mutex_init(&fork1->mutex, NULL))
	{
		free(fork1);
		return (NULL);
	}
	return (fork1);
}

t_philo	set_philo(t_fork *fork1, t_fork *fork2, int i)
{
	t_philo	philo;

	philo.seat = i + 1;
	philo.fork_left = fork1;
	philo.fork_right = fork2;
	return (philo);
}

int	give_fork_to_philo(t_table table, t_fork *fork1, t_fork *fork2, int i)
{
	if (!fork1 || !fork2)
		return (1);
	table.table[i] = set_philo(fork1, fork2, i);
	return (0);
}

t_table	seating_arrangement(t_table table)
{
	unsigned int	i;

	i = -1;
	while (++i < table.nb_chair)
	{
		if (i == 0)
		{
			if (give_fork_to_philo(table, set_fork(), set_fork(), i))
				return (free_table(table, i));
		}
		else if (i == table.nb_chair - 1)
		{
			if (give_fork_to_philo(table, table.table[0].fork_right,
					table.table[i - 1].fork_left, i))
				return (free_table(table, i));
		}
		else
		{
			if (give_fork_to_philo(table, set_fork(),
					table.table[i - 1].fork_left, i))
				return (free_table(table, i));
		}
	}
	return (table);
}

t_table	set_the_table(t_data data)
{
	t_table	table;
	t_fork	*fork;

	table.nb_chair = data.nb_philo;
	table.table = malloc(sizeof(t_philo) * table.nb_chair);
	if (!table.table)
		return (table);
	if (data.nb_philo == 1)
	{
		fork = set_fork();
		if (give_fork_to_philo(table, fork, fork, 0))
			return (free_table(table, 0));
	}
	else
		table = seating_arrangement(table);
	return (table);
}
