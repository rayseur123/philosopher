/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_must_eat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 06:26:24 by njooris           #+#    #+#             */
/*   Updated: 2025/07/29 07:35:41 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dinner.h"
#include <unistd.h>

int	upt_count_must_eat(t_pack_data p_data)
{
	pthread_mutex_lock(&p_data.have_eat->mutex);
	p_data.have_eat->count_have_eat--;
	pthread_mutex_unlock(&p_data.have_eat->mutex);
	return (0);
}

unsigned long	get_count_must_eat(t_pack_data p_data)
{
	unsigned long	val;

	pthread_mutex_lock(&p_data.have_eat->mutex);
	val = p_data.have_eat->count_have_eat;
	pthread_mutex_unlock(&p_data.have_eat->mutex);
	return (val);
}
