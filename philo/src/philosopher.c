/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:53:50 by njooris           #+#    #+#             */
/*   Updated: 2025/07/21 14:01:59 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "dinner.h"
#include "parsing.h"


t_pack_data	*init_packdata(unsigned long int time_start, t_time_to time_to, t_philo *philo, t_start *start)
{
	t_pack_data		*p_data;

	p_data = malloc(sizeof(t_pack_data));
	if (!p_data)
		return (NULL);
	p_data->start = start;
	p_data->time_to = time_to;
	p_data->timestart = time_start;
	p_data->philo = philo;
	return (p_data);
}

unsigned long	time_start_init()
{
	struct timeval	tv;
  	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	try_fork(t_pack_data *p_data, t_fork *fork)
{
	bool	val;
	int		check;

	check = 1;
	val = 1;
	while (val)
	{
		pthread_mutex_lock(&p_data->start->mutex);
		check = p_data->start->start;
		pthread_mutex_unlock(&p_data->start->mutex);
		if (!check)
			return (1);
		pthread_mutex_lock(&fork->mutex);
		val = fork->fork;
		if (!val)
		{
			print_timestamp_philo(*p_data, TAKE_FORK);
			fork->fork = 1;
		}
		pthread_mutex_unlock(&fork->mutex);
	}
	return (0);
}

int	drop_fork(t_fork *fork_left, t_fork *fork_right)
{
	pthread_mutex_lock(&fork_left->mutex);
	fork_left->fork = 0;
	pthread_mutex_unlock(&fork_left->mutex);
	pthread_mutex_lock(&fork_right->mutex);
	fork_right->fork = 0;
	pthread_mutex_unlock(&fork_right->mutex);
	return (0);
}

int	philo_eat(t_pack_data *p_data)
{
	unsigned long	start_think;

	print_timestamp_philo(*p_data, THINK);
	start_think = time_start_init();
	if (p_data->philo->seat % 2)
	{
		try_fork(p_data, p_data->philo->fork_left);
		try_fork(p_data, p_data->philo->fork_right);
		print_timestamp_philo(*p_data, EAT);
		p_data->philo->last_eat = time_start_init();
		if (ft_msleep_check_last_eat(p_data->time_to.time_to_eat, *p_data))
			return (1);
		drop_fork(p_data->philo->fork_left, p_data->philo->fork_right);
	}
	else
	{
		try_fork(p_data, p_data->philo->fork_right);
		try_fork(p_data, p_data->philo->fork_left);
		print_timestamp_philo(*p_data, EAT);
		p_data->philo->last_eat = time_start_init();
		if (ft_msleep_check_last_eat(p_data->time_to.time_to_eat, *p_data))
			return (1);
		drop_fork(p_data->philo->fork_right, p_data->philo->fork_left);
	}
	return (0);
}

int	philo_sleep(t_pack_data *p_data)
{
	print_timestamp_philo(*p_data, SLEEP);
	if (ft_msleep_check_last_eat(p_data->time_to.time_to_sleep, *p_data))
		return (1);
	return (0);
}

void	*do_actions(void *data)
{
	t_pack_data	*p_data;
	bool 		check;
	unsigned int			i;

	i = 0;
	p_data = (t_pack_data *)data;
	check = 0;
	while (!check)
	{
		pthread_mutex_lock(&p_data->start->mutex);
		check = p_data->start->start;
		pthread_mutex_unlock(&p_data->start->mutex);
	}
	while(1)
	{
		if (philo_eat(p_data))
			return (NULL);
		i++;
		if (i == p_data->time_to.time_must_eat)
		{
			pthread_mutex_lock(&p_data->mutex);
			(*p_data->nb_philo)--;
			pthread_mutex_unlock(&p_data->mutex);
		}
		pthread_mutex_lock(&p_data->mutex);
		if (!*p_data->nb_philo)
		{
			pthread_mutex_unlock(&p_data->mutex);
			return (0);
		}
		pthread_mutex_unlock(&p_data->mutex);
		if (philo_sleep(p_data))
			return (NULL);
	}
	return (NULL);
}

void	start_simulation(t_table table, t_time_to time_to)
{
	unsigned int					i;
	unsigned long int				time_start;
	t_pack_data						*p_data;
	t_start							start;
	unsigned int					nb_philo;

	i = 0;
	start.start = 0;
	time_start = time_start_init();
	pthread_mutex_init(&start.mutex, NULL);
	nb_philo = table.nb_chair;
	while(i < nb_philo)
	{
		p_data = init_packdata(time_start, time_to, &table.table[i], &start);
		p_data->nb_philo = &nb_philo;
		if (!p_data || pthread_create(&table.table[i].thread, NULL, &do_actions, p_data) == -1)
			break ;
		i++;
	}
	printf("Start simulation !\n");
	pthread_mutex_lock(&start.mutex);
	start.start = 1;
	pthread_mutex_unlock(&start.mutex);
	while(--i >= 0)
	{
		pthread_join(table.table[i].thread, NULL);
		if (i == 0)
			break;
	}
}

void	philosopher(t_data data)
{
	t_table			table;
	t_time_to		time_to;

	table = set_the_table(data);
	time_to = set_time_to(data);
	if (!table.table)
	{
		printf("MALLOC ERROR\n");
		return ;
	}
	start_simulation(table, time_to);
	free_table(table, table.nb_chair);
}
