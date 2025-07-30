/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:18:57 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 09:05:41 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "dinner.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned long	get_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

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
		negativ *= 44 - nptr[x++];
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

	i = -1;
	while (++i < size_malloc)
	{
		pthread_mutex_destroy(&table.table[i].fork_right->mutex);
		free(table.table[i].fork_right);
	}
	free(table.table);
	table.table = NULL;
	return (table);
}

t_time_to	set_time_to(t_data data)
{
	t_time_to	time;

	time.time_must_eat = data.time_must_eat;
	time.time_to_die = data.time_to_die;
	time.time_to_eat = data.time_to_eat;
	time.time_to_sleep = data.time_to_sleep;
	time.time_start = get_time();
	return (time);
}
