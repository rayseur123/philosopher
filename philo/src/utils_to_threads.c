/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 06:19:34 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 07:57:32 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner.h"
#include <stdio.h>
#include <unistd.h>

int	ft_msleep(unsigned long time, t_pack_data p_data)
{
	int				check;
	unsigned long	time_start;

	check = 1;
	time_start = get_time();
	while (get_time() - time_start < time)
	{
		pthread_mutex_lock(&p_data.is_dead->mutex);
		check = p_data.is_dead->is_dead;
		if (check)
		{
			pthread_mutex_unlock(&p_data.is_dead->mutex);
			return (1);
		}
		pthread_mutex_unlock(&p_data.is_dead->mutex);
		if ((get_time() - p_data.philo->last_eat)
			>= p_data.time_to.time_to_die)
		{
			print_timestamp_philo(p_data, DEAD);
			return (1);
		}
		usleep(100);
	}
	return (0);
}

void	print_timestamp_philo(t_pack_data p_data, int action)
{
	unsigned long int	timestamp;
	bool				check;

	pthread_mutex_lock(p_data.mutex_printf);
	pthread_mutex_lock(&p_data.is_dead->mutex);
	timestamp = get_time() - p_data.time_to.time_start;
	check = p_data.is_dead->is_dead;
	if (!p_data.is_dead->is_dead && action == DEAD)
	{
		printf("%lu %d is died\n", timestamp, p_data.philo->seat);
		p_data.is_dead->is_dead = 1;
	}
	pthread_mutex_unlock(&p_data.is_dead->mutex);
	if (action == TAKE_FORK && !check)
		printf("%lu %d has taken a fork\n", timestamp, p_data.philo->seat);
	else if (action == THINK && !check)
		printf("%lu %d is thinking\n", timestamp, p_data.philo->seat);
	else if (action == EAT && !check)
		printf("%lu %d is eating\n", timestamp, p_data.philo->seat);
	else if (action == SLEEP && !check)
		printf("%lu %d is sleeping\n", timestamp, p_data.philo->seat);
	pthread_mutex_unlock(p_data.mutex_printf);
}
