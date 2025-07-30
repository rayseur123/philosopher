/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:18:09 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 07:55:48 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_data	parsing(int ac, char **av, int *check)
{
	t_data	data;

	data.nb_philo = ft_atoi(av[1], check);
	data.time_to_die = ft_atoi(av[2], check);
	data.time_to_eat = ft_atoi(av[3], check);
	data.time_to_sleep = ft_atoi(av[4], check);
	if (ac == 6)
	{
		data.time_must_eat = ft_atoi(av[5], check);
		if (av[5][0] == '-')
			*check = 0;
	}
	else
		data.time_must_eat = -1;
	if (av[1][0] == '-' || av[2][0] == '-' || av[3][0] == '-'
		|| av[4][0] == '-')
		*check = 0;
	return (data);
}
