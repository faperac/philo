/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_philo1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:41:16 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/12 15:43:31 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	resultat;
	int	nbsigne;

	nbsigne = 1;
	i = 0;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		if (str[i] == '-')
			nbsigne = nbsigne * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		resultat = resultat * 10 + str[i] - '0';
		if (!(str[i] >= 48 && str[i] <= 57))
			return (resultat * nbsigne);
		i++;
	}
	return (resultat * nbsigne);
}

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		timems;

	gettimeofday(&time, NULL);
	timems = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (timems);
}

void	ft_usleep(unsigned int time, t_env *data)
{
	unsigned int	end_time;

	if (time > 0)
	{
		end_time = get_time_ms() + time;
		while ((unsigned int) get_time_ms() < end_time)
			usleep(data->philo_nb * 2);
	}
}
