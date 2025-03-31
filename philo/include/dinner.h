/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:24:38 by njooris           #+#    #+#             */
/*   Updated: 2025/03/28 14:42:13 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINNER_H
# define DINNER_H
# include <stdbool.h>
# include <pthread.h>
# include "parsing.h"

enum e_etat
{
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
	int		seat;
	int		etat;
	t_fork	*fork_left;
	t_fork	*fork_right;
}	t_philo;

typedef struct s_table
{
	t_philo	*table;
	int		nb_chair;
}	t_table;

// seter
t_fork	*set_fork();
t_philo	set_philo(t_fork *fork1, t_fork *fork2, int i);
t_table	set_the_table(t_data data);

// link table
int	give_fork_to_philo(t_table table, t_fork *fork1, t_fork *fork2, int i);
t_table	seating_arrangement(t_table table);

// other
t_table	free_table(t_table table, int size_malloc);
void	philosopher(t_data data);

#endif