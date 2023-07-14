/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:30:03 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/13 11:08:51 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_arg(int argc, char **argv, t_env *data)
{
	check_only_number(argv);
	if (argc == 5 || argc == 6)
	{
		data->philo_nb = ft_atoi(argv[1]);
		data->die = ft_atoi(argv[2]);
		data->eat = ft_atoi(argv[3]);
		data->sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->nb_eat = ft_atoi(argv[5]);
		else
			data->nb_eat = 99999999;
	}
	if ((data->philo_nb > 0 && data->die > 0
			&& data->eat > 0 && data->sleep > 0))
		return ;
	exit(EXIT_FAILURE);
}

void	check_only_number(char **argv)
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
				exit(EXIT_FAILURE);
			y++;
		}
		i++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
