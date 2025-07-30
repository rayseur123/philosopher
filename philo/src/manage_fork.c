/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 06:28:42 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 09:32:08 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner.h"
#include <unistd.h>

int	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->fork = 0;
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	have_to_stop(t_pack_data p_data)
{
	pthread_mutex_lock(&p_data.is_dead->mutex);
	if (p_data.is_dead->is_dead)
	{
		pthread_mutex_unlock(&p_data.is_dead->mutex);
		return (1);
	}
	pthread_mutex_unlock(&p_data.is_dead->mutex);
	return (0);
}

int	i_am_dead(t_pack_data p_data)
{
	if ((get_time() - p_data.philo->last_eat) >= p_data.time_to.time_to_die)
	{
		print_timestamp_philo(p_data, DEAD);
		return (1);
	}
	return (0);
}

int	take_fork(t_pack_data *p_data, t_fork *fork1, t_fork *fork2, int val)
{
	while (val != 2)
	{
		if (have_to_stop(*p_data) || i_am_dead(*p_data))
			return (1);
		pthread_mutex_lock(&fork1->mutex);
		if (!fork1->fork)
		{
			print_timestamp_philo(*p_data, TAKE_FORK);
			fork1->fork = 1;
			val++;
		}
		pthread_mutex_unlock(&fork1->mutex);
		pthread_mutex_lock(&fork2->mutex);
		if (!fork2->fork)
		{
			print_timestamp_philo(*p_data, TAKE_FORK);
			fork2->fork = 1;
			val++;
		}
		pthread_mutex_unlock(&fork2->mutex);
		usleep(100);
	}
	return (0);
}
