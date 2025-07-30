/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pack_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:53:31 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 08:14:14 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner.h"
#include <stdlib.h>

int	init_all_mutex(t_have_eat **have_eat, t_is_dead **is_dead,
		t_start_threads **start, unsigned int i)
{
	*have_eat = NULL;
	*is_dead = NULL;
	*start = NULL;
	*have_eat = malloc(sizeof(t_have_eat));
	if (!*have_eat)
		return (1);
	*is_dead = malloc(sizeof(t_is_dead));
	if (!*is_dead)
		return (1);
	*start = malloc(sizeof(t_start_threads));
	if (!*start)
		return (1);
	if (pthread_mutex_init(&(*have_eat)->mutex, NULL)
		|| pthread_mutex_init(&(*is_dead)->mutex, NULL)
		|| pthread_mutex_init(&(*start)->mutex, NULL))
		return (1);
	(*have_eat)->count_have_eat = i;
	(*is_dead)->is_dead = 0;
	(*start)->start = 0;
	return (0);
}

void	set_mutex_to_p_data(t_pack_data **p_data, t_have_eat *have_eat,
		t_is_dead *is_dead, t_start_threads *start)
{
	(*p_data)->have_eat = have_eat;
	(*p_data)->start_threads = start;
	(*p_data)->is_dead = is_dead;
}

t_pack_data	*init_pack_data(t_time_to time_to, t_philo *philo)
{
	t_pack_data		*p_data;

	p_data = malloc(sizeof(t_pack_data));
	if (!p_data)
		return (NULL);
	p_data->philo = philo;
	p_data->time_to = time_to;
	return (p_data);
}
