/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:30:03 by fabperei          #+#    #+#             */
/*   Updated: 2023/09/12 11:21:27 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_env	*ft_init_arg(char **argv, t_env *data)
{
	data->one_dead = 0;
	data->philo_nb = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (argv[5])
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
	pthread_mutex_init(&(data->display), NULL);
	pthread_mutex_init(&(data->dead_mutex), NULL);
	pthread_mutex_init(&(data->eat_mutex), NULL);
	pthread_mutex_init(&(data->stop), NULL);
	return (data);
}

int	check_arg(int argc, char **argv)
{
	if (check_only_number(argv))
	{
		ft_error("Only input number are accepted");
		return (0);
	}
	if ((argc == 5 || argc == 6))
	{
		if ((ft_atoi(argv[1]) > 0 && ft_atoi(argv[2]) > 0
				&& ft_atoi(argv[3]) > 0 && ft_atoi(argv[4]) > 0))
			return (1);
	}
	else
		ft_error("Wrong number of arguments");
	return (0);
}

int	check_only_number(char **argv)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	while (argv[i])
	{
		y = 0;
		while (argv[i][y])
		{
			if (!ft_isdigit(argv[i][y]))
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_error(char *msg)
{
	printf(RED"Error: %s\n"RESET, msg);
	return (1);
}
