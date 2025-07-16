/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:24:38 by njooris           #+#    #+#             */
/*   Updated: 2025/07/16 11:57:02 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINNER_H
# define DINNER_H
# include <stdbool.h>
# include "parsing.h"

enum e_etat
{
	TAKE_FORK,
	THINK,
	EAT,
	SLEEP,
	DEAD
};

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			fork;
}	t_fork;

typedef struct s_philo
{
	pthread_mutex_t			mutex;
	pthread_t				thread;
	unsigned int			seat;
	unsigned long			last_eat;
	unsigned int			etat;
	t_fork					*fork_left;
	t_fork					*fork_right;
}	t_philo;

typedef struct s_table
{
	t_philo	*table;
	unsigned int		nb_chair;
}	t_table;

typedef struct s_start
{
	bool	start;
	pthread_mutex_t	mutex;
}	t_start;

typedef struct s_have_eat
{
	pthread_mutex_t	mutex;
	unsigned int	have_eat;
}	t_have_eat;

typedef struct s_pack_data
{
	unsigned int				*nb_philo;
	pthread_mutex_t				mutex;
	t_have_eat					have_eat;
	t_philo						*philo;
	unsigned long int			timestart;
	t_time_to 					time_to;
	t_start						*start;
}	t_pack_data;

// seter
t_fork	*set_fork();
t_philo	set_philo(t_fork *fork1, t_fork *fork2, int i);
t_table	set_the_table(t_data data);

// link table
int	give_fork_to_philo(t_table table, t_fork *fork1, t_fork *fork2, int i);
t_table	seating_arrangement(t_table table);

// other
t_table		free_table(t_table table, unsigned int size_malloc);
void		philosopher(t_data data);
void		ft_msleep(int time);
int			ft_msleep_check_last_eat(int time, t_pack_data p_data);
void		print_timestamp_philo(t_pack_data p_data, int action);
unsigned long	time_start_init();

#endif