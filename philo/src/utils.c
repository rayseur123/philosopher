/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njooris <njooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:18:57 by njooris           #+#    #+#             */
/*   Updated: 2025/03/28 10:07:14 by njooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int x)
{
	return (x >= '0' && x <= '9');
}

int	ft_atoi(const char *nptr, int *check) // edit cet atoi pour ne recevoir que des nombres
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
	{
		negativ *= 44 - nptr[x];
		x++;
	}
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

