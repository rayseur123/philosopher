/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:01:05 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 07:33:21 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <pthread.h>

typedef struct s_data
{
	unsigned long int	nb_philo;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	unsigned long int	time_must_eat;

}	t_data;

typedef struct s_time_to
{
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	long int			time_must_eat;
	unsigned long int	time_start;
}	t_time_to;

int			ft_atoi(const char *nptr, int *check);
t_data		parsing(int ac, char **av, int *check);
t_time_to	set_time_to(t_data data);

void		philosopher(t_data data);

#endif