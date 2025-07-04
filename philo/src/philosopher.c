/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:53:50 by njooris           #+#    #+#             */
/*   Updated: 2025/07/04 16:08:52 by njooris          ###   ########.fr       */
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

void	display_pdt(t_pack_data	p_data)
{
	printf("PHILO : \n");
	printf("fork right : %d\n", p_data.philo->etat);
	printf("fork left : %p\n", p_data.philo->fork_left);
	printf("fork right : %p\n", p_data.philo->fork_right);
	printf("seat : %d\n", p_data.philo->seat);
	printf("TIME TO : \n");
	printf("time must eat : %lu\n", p_data.time_to.time_must_eat);
	printf("time to die : %lu\n", p_data.time_to.time_to_die);
	printf("time to eat : %lu\n", p_data.time_to.time_to_eat);
	printf("time to sleep : %lu\n", p_data.time_to.time_to_sleep);
	printf("time start : %lu\n", p_data.timestart);
	printf("\n");
}

unsigned long	time_start_init()
{
	struct timeval	tv;
  	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	try_fork_left(t_pack_data *p_data)
{
	bool	val;

	val = 1;
	while (val)
	{
		pthread_mutex_lock(&p_data->philo->fork_left->mutex);
		val = p_data->philo->fork_left->fork;
		if (!val)
		{
			print_timestamp_philo(p_data->philo->seat, TAKE_FORK, p_data->timestart);
			p_data->philo->fork_left->fork = 1;
		}
		pthread_mutex_unlock(&p_data->philo->fork_left->mutex);
		if (val)
			ft_msleep(1);
	}
	return (0);
}

int	try_fork_right(t_pack_data *p_data)
{
	bool	val;

	val = 1;
	while (val)
	{
		pthread_mutex_lock(&p_data->philo->fork_right->mutex);
		val = p_data->philo->fork_right->fork;
		if (!val)
		{
			print_timestamp_philo(p_data->philo->seat, TAKE_FORK, p_data->timestart);
			p_data->philo->fork_right->fork = 1;
		}
		pthread_mutex_unlock(&p_data->philo->fork_right->mutex);
		if (val)
			ft_msleep(1);
	}
	return (0);
}

int	drop_fork_right(t_pack_data *p_data)
{
	pthread_mutex_lock(&p_data->philo->fork_right->mutex);
	p_data->philo->fork_right->fork = 0;
	pthread_mutex_unlock(&p_data->philo->fork_right->mutex);
	pthread_mutex_lock(&p_data->philo->fork_left->mutex);
	p_data->philo->fork_left->fork = 0;
	pthread_mutex_unlock(&p_data->philo->fork_left->mutex);
	return (0);
}

int	drop_fork_left(t_pack_data *p_data)
{
	pthread_mutex_lock(&p_data->philo->fork_left->mutex);
	p_data->philo->fork_left->fork = 0;
	pthread_mutex_unlock(&p_data->philo->fork_left->mutex);
	pthread_mutex_lock(&p_data->philo->fork_right->mutex);
	p_data->philo->fork_right->fork = 0;
	pthread_mutex_unlock(&p_data->philo->fork_right->mutex);
	return (0);
}

int	philo_eat(t_pack_data *p_data)
{
	unsigned long	start_think;

	print_timestamp_philo(p_data->philo->seat, THINK, p_data->timestart);
	start_think = time_start_init(); // utiliser pour check si le philo prend trop de temps
	if (p_data->philo->seat % 2)
	{	
		try_fork_left(p_data);
		try_fork_right(p_data);
		print_timestamp_philo(p_data->philo->seat, EAT, p_data->timestart);
		p_data->philo->last_eat = time_start_init();
		if (ft_msleep_check_last_eat(p_data->time_to.time_to_eat, *p_data))
			return (1);
		drop_fork_left(p_data);
	}
	else
	{
		try_fork_right(p_data);
		try_fork_left(p_data);
		print_timestamp_philo(p_data->philo->seat, EAT, p_data->timestart);
		p_data->philo->last_eat = time_start_init();
		if (ft_msleep_check_last_eat(p_data->time_to.time_to_eat, *p_data))
			return (1);
		drop_fork_right(p_data);
	}
	return (0);
}

int	philo_sleep(t_pack_data *p_data)
{
	print_timestamp_philo(p_data->philo->seat, SLEEP, p_data->timestart);
	if (ft_msleep_check_last_eat(p_data->time_to.time_to_sleep, *p_data))
		return (1);
	return (0);
}


void	*do_actions(void *data) // on est dans le thread ici
{
	t_pack_data	*p_data;
	bool 		check;

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

	i = 0;
	time_start = time_start_init();
	pthread_mutex_init(&start.mutex, NULL);
	start.start = 0;
	while(i < table.nb_chair)
	{
		p_data = init_packdata(time_start, time_to, &table.table[i], &start);
		if (!p_data || pthread_create(&table.table[i].thread, NULL, &do_actions, p_data) == -1)
			break ;
		i++;
	}
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
