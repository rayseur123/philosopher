/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:55:12 by njooris           #+#    #+#             */
/*   Updated: 2025/03/28 14:37:25 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parsing.h"
#include "dinner.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		check;

	check = 1;
	if(ac < 5 || ac > 6)
	{
		printf("BAD PARAMS\n");
		return(1);
	}
	data = parsing(ac, av, &check);
	if (!check)
	{
		printf("BAD PARAMS\n");
		return(1);
	}
	philosopher(data);
	return (0);
}