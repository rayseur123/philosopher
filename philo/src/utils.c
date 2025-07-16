/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:18:57 by njooris           #+#    #+#             */
/*   Updated: 2025/07/16 12:49:18 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "dinner.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_isdigit(int x)
{
	return (x >= '0' && x <= '9');
}

int	ft_atoi(const char *nptr, int *check)
{
	int				x;
	long long int	val;
	int				negativ;

	val = 0;
	negativ = 1;
	x = 0;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || nptr[x] == ' ')
		x++;
	if (nptr[x] == '-' || nptr[x] == '+')
	{
		negativ *= 44 - nptr[x];
		x++;
	}
	while (nptr[x] != '\0' && ft_isdigit(nptr[x]))
	{
		if ((10 * val + (nptr[x] - '0')) / 10 != val)
		{
			*check = 0;
			return (-1 * (negativ > 0));
		}
		val = 10 * val + (nptr[x++] - '0');
	}
	if (!ft_isdigit(nptr[x]) && nptr[x] != '\0')
		*check = 0;
	return (val * negativ);
}

t_table	free_table(t_table table, unsigned int size_malloc)
{
	unsigned int	i;

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

t_time_to set_time_to(t_data data)
{
	t_time_to time;

	time.time_must_eat = data.time_must_eat;
	time.time_to_die = data.time_to_die;
	time.time_to_eat = data.time_to_eat;
	time.time_to_sleep = data.time_to_sleep;
	return (time); 
}

void	ft_msleep(int time)
{
	usleep(time * 1000);
}

int		ft_msleep_check_last_eat(int time, t_pack_data p_data)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (i < time) // pontentielement changer la condition de la boucle
	{
		usleep(1000);
		pthread_mutex_lock(&p_data.start->mutex);
		check = p_data.start->start;
		pthread_mutex_unlock(&p_data.start->mutex);
		if (!check)
			return (1);
		if ((time_start_init() - p_data.philo->last_eat) >= p_data.time_to.time_to_die)
		{
			print_timestamp_philo(p_data, DEAD);
			return (1);
		}
		++i;
	}
	return (0);
}

void	print_timestamp_philo(t_pack_data p_data, int action)
{
	unsigned long int	timestamp;
	int					check;

	check = 1;
	timestamp = time_start_init() - p_data.timestart;
	pthread_mutex_lock(&p_data.start->mutex);
	check = p_data.start->start;
	if (check && action == DEAD)
	{
		if (p_data.start->start)
			printf("%lu %d died\n", timestamp, p_data.philo->seat);
		p_data.start->start = 0;
	}
	pthread_mutex_unlock(&p_data.start->mutex);
	if (!check)
		return ;
	pthread_mutex_lock(&p_data.mutex);
	if (action == TAKE_FORK)
		printf("%lu %d has taken a fork\n",  timestamp, p_data.philo->seat);
	else if (action == THINK)
		printf("%lu %d is thinking\n", timestamp, p_data.philo->seat);
	else if (action == EAT)
		printf("%lu %d is eating\n", timestamp, p_data.philo->seat);
	else if (action == SLEEP)
		printf("%lu %d is sleeping\n", timestamp, p_data.philo->seat);
}
