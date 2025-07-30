/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:57:52 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 09:32:23 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner.h"
#include <stdlib.h>
#include <unistd.h>

void	wait_all_threads(t_pack_data *p_data)
{
	bool	check;

	check = 0;
	while (!check)
	{
		pthread_mutex_lock(&p_data->start_threads->mutex);
		check = p_data->start_threads->start;
		p_data->time_to.time_start = p_data->start_threads->start;
		pthread_mutex_unlock(&p_data->start_threads->mutex);
		usleep(50);
	}
}

int	philo_eat(t_pack_data *p_data)
{
	unsigned long	start_think;

	start_think = get_time();
	print_timestamp_philo(*p_data, THINK);
	if (p_data->philo->seat % 2)
	{
		if (take_fork(p_data, p_data->philo->fork_left,
				p_data->philo->fork_right, 0))
			return (1);
	}
	else
	{
		if (take_fork(p_data, p_data->philo->fork_right,
				p_data->philo->fork_left, 0))
			return (1);
	}
	print_timestamp_philo(*p_data, EAT);
	p_data->philo->last_eat = get_time();
	ft_msleep(p_data->time_to.time_to_eat, *p_data);
	drop_fork(p_data->philo->fork_left);
	drop_fork(p_data->philo->fork_right);
	return (0);
}

int	philo_sleep(t_pack_data *p_data)
{
	print_timestamp_philo(*p_data, SLEEP);
	if (ft_msleep(p_data->time_to.time_to_sleep, *p_data))
		return (1);
	return (0);
}

void	*philo(void	*data)
{
	t_pack_data	*p_data;
	int			count_eat;

	count_eat = 0;
	p_data = (t_pack_data *)data;
	wait_all_threads(p_data);
	p_data->philo->last_eat = get_time();
	if (p_data->philo->seat % 2)
		usleep(25000);
	while (1)
	{
		if (philo_eat(p_data))
			break ;
		count_eat++;
		if (count_eat == p_data->time_to.time_must_eat)
			upt_count_must_eat(*p_data);
		if (get_count_must_eat(*p_data) <= 0)
			break ;
		if (philo_sleep(p_data))
			break ;
	}
	free(p_data);
	return (NULL);
}
