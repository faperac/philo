/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:30:03 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/02 15:46:08 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_arg(int argc, char **argv, t_env  *data)
{
	if (argc == 5 || argc == 6)
	{
		data->philo = ft_atoi(argv[1]);
		data->die = ft_atoi(argv[2]);
		data->eat = ft_atoi(argv[3]);
		data->sleep = ft_atoi(argv[4]);
		if (argc == 6)
			data->nb_eat = ft_atoi(argv[5]);
	}
	if ((data->philo > 0 || data->die > 0 || data->eat > 0 || data->sleep > 0) || data->die <= (data->eat + data->sleep))
		return ;
	exit(EXIT_FAILURE);
}

