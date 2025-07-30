/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:03:38 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 09:10:47 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner.h"
#include <stdlib.h>
#include <stdio.h>

void	wait_threads(t_table table, int i)
{
	while (--i > -1)
		pthread_join(table.table[i].thread, NULL);
}

void	start_threads(t_start_threads *start)
{
	pthread_mutex_lock(&start->mutex);
	start->start = get_time();
	printf("Simulation start !\n");
	pthread_mutex_unlock(&start->mutex);
}

void	free_all_mutex(t_have_eat *have_eat, t_is_dead *is_dead,
		t_start_threads *start)
{
	free(have_eat);
	free(is_dead);
	free(start);
}

int	start_simulation(t_table table, t_time_to time_to, t_pack_data *p_data)
{
	t_have_eat		*have_eat;
	t_is_dead		*is_dead;
	t_start_threads	*start;
	unsigned int	i;
	pthread_mutex_t	mutex_printf;

	if (!init_all_mutex(&have_eat, &is_dead, &start, table.nb_chair)
		&& !pthread_mutex_init(&mutex_printf, NULL))
	{
		i = -1;
		while (++i < table.nb_chair)
		{
			p_data = init_pack_data(time_to, &table.table[i]);
			if (!p_data)
				break ;
			set_mutex_to_p_data(&p_data, have_eat, is_dead, start);
			p_data->mutex_printf = &mutex_printf;
			if (pthread_create(&table.table[i].thread, NULL, &philo, p_data))
				break ;
		}
		start_threads(start);
		wait_threads(table, i);
	}
	free_all_mutex(have_eat, is_dead, start);
	return (0);
}

void	philosopher(t_data data)
{
	t_table		table;
	t_time_to	time_to;
	t_pack_data	p_data;

	table = set_the_table(data);
	if (!table.table)
		return ;
	time_to = set_time_to(data);
	start_simulation(table, time_to, &p_data);
	free_table(table, table.nb_chair);
	return ;
}
