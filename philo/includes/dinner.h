/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:24:38 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 09:33:32 by njooris          ###   ########.fr       */
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
	DEAD,
	NONE
};

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			fork;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	seat;
	unsigned long	last_eat;
	t_fork			*fork_left;
	t_fork			*fork_right;
	unsigned int	count_fork;
}	t_philo;

typedef struct s_table
{
	t_philo			*table;
	unsigned int	nb_chair;
}	t_table;

typedef struct s_start_threads
{
	unsigned long			start;
	pthread_mutex_t			mutex;
}	t_start_threads;

typedef struct s_is_dead
{
	bool			is_dead;
	pthread_mutex_t	mutex;
}	t_is_dead;

typedef struct s_have_eat
{
	unsigned int	count_have_eat;
	pthread_mutex_t	mutex;
}	t_have_eat;

typedef struct s_pack_data
{
	pthread_mutex_t	*mutex_printf;
	t_philo			*philo;		
	t_time_to		time_to;
	t_have_eat		*have_eat;
	t_is_dead		*is_dead;
	t_start_threads	*start_threads;
}	t_pack_data;

t_table			free_table(t_table table, unsigned int size_malloc);
unsigned long	get_time(void);

// seter
t_fork			*set_fork(void);
t_philo			set_philo(t_fork *fork1, t_fork *fork2, int i);
t_table			set_the_table(t_data data);

// link table
int				give_fork_to_philo(t_table table, t_fork *fork1,
					t_fork *fork2, int i);
t_table			seating_arrangement(t_table table);

// pack data manage
int				init_all_mutex(t_have_eat **have_eat, t_is_dead **is_dead,
					t_start_threads **start, unsigned int i);
void			set_mutex_to_p_data(t_pack_data **p_data, t_have_eat *have_eat,
					t_is_dead *is_dead, t_start_threads *start);
t_pack_data		*init_pack_data(t_time_to time_to, t_philo *philo);

// do philo
void			*philo(void	*p_data);
int				ft_msleep(unsigned long time, t_pack_data p_data);
void			print_timestamp_philo(t_pack_data p_data, int action);
int				drop_fork(t_fork *fork);
int				take_fork(t_pack_data *p_dt, t_fork *frk1, t_fork *frk2, int i);
int				upt_count_must_eat(t_pack_data p_data);
unsigned long	get_count_must_eat(t_pack_data p_data);

#endif