/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/09/13 15:35:32 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_spleet_think(t_philo *philo)
{
	ft_display(philo, philo->id, EAT);
	pthread_mutex_lock(&(philo->env->eat_mutex));
	philo->last_eat = get_time_ms();
	philo->nb_of_eat++;
	pthread_mutex_unlock(&(philo->env->eat_mutex));
	ft_usleep(philo->env->eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	ft_display(philo, philo->id, SLEEP);
	ft_usleep(philo->env->sleep);
	ft_display(philo, philo->id, THINK);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep((philo->env->eat / 10));
	while (!check_dead(philo, 0))
	{
		pthread_create(&t, NULL, &dead_philo, arg);
		take_fork(philo);
		eat_spleet_think(philo);
		pthread_detach(t);
		if (philo->nb_of_eat == philo->env->nb_eat)
		{
			pthread_mutex_unlock(&philo->env->stop);
			check_dead(philo, 1);
			return (NULL);
		}
	}
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	ft_display(philo, philo->id, FORK);
	if (philo->env->philo_nb == 1)
	{
		ft_usleep(philo->env->die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	ft_display(philo, philo->id, FORK);
	return ;
}

int	init_all_philo(t_env *data)
{
	int			i;

	i = -1;
	data->start_time = get_time_ms();
	while (++i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_eat = 0;
		data->philos[i].nb_of_eat = 0;
		data->philos[i].env = data;
		data->philos[i].fork_r = NULL;
		pthread_mutex_init(&(data->philos[i].fork_l), NULL);
		if (i == data->philo_nb - 1)
			data->philos[i].fork_r = &data->philos[0].fork_l;
		else
			data->philos[i].fork_r = &data->philos[i + 1].fork_l;
		if (pthread_create(&data->philos[i].thread, NULL, \
			&philo_routine, &data->philos[i]) == -1)
			return (-1);
	}
	i = -1;
	while (++i < data->philo_nb)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	*data;

	if (!check_arg(argc, argv))
		return (1);
	data = malloc(sizeof(t_env));
	if (!data)
		return (1);
	data = ft_init_arg(argv, data);
	if (init_all_philo(data))
		return (1);
	ft_free(data);
	return (0);
}
