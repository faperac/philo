/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/14 15:42:49 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	long long time_eat;

	time_eat = get_time_ms() - philo->start_t;
	philo->last_eat = get_time_ms();
	ft_usleep(philo->env->eat, philo->env);
	ft_display(philo, philo->id, EAT);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	psleep(philo);
	think(philo);
	philo->nb_of_eat++;
}

void	psleep(t_philo *philo)
{
	ft_usleep(philo->env->sleep, philo->env);
	ft_display(philo, philo->id, SLEEP);
}

void	think(t_philo *philo)
{
	ft_display(philo, philo->id, THINK);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0 && philo->nb_of_eat < 1)
		ft_usleep((philo->env->eat / 10), philo->env);
	while (philo->nb_of_eat < philo->env->nb_eat)
	{
		take_fork(philo);
		eat(philo);
	}
	return (NULL);
}

int		check_dead(t_philo *philo)
{

	if (philo->last_eat >= philo->env->die)
		philo->env->is_dead = 1;
	if (philo->env->is_dead == 1)
	{
		//dead_philo(philo);
		return (1);
	}
	return (0);
}

void	dead_philo(t_philo *philo)
{
	ft_display(philo, philo->id, DIED);
}

void	take_fork(t_philo *philo)
{
	//check_dead(philo);
	pthread_mutex_lock(&(philo->fork_l));
	ft_display(philo, philo->id, FORK);
	if (philo->env->philo_nb == 1)
	{
		ft_usleep(philo->env->die * 2, philo->env);
		check_dead(philo);
	}
	ft_display(philo, philo->id, FORK);
	//check_dead(philo);
	//pthread_mutex_lock(&data->forks[fork_i]);
	return ;
}

void	create_philo(t_env *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	init_all_philo(t_env *data)
{
	int			i;
	long long	s_t;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		exit(EXIT_FAILURE);
	s_t = get_time_ms();
	pthread_mutex_init(&(data->display), NULL);
	pthread_mutex_init(&(data->dead_mutex), NULL);
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_eat = 0;
		data->philos[i].nb_of_eat = 0;
		data->philos[i].start_t = s_t;
		data->philos[i].env = data;
		data->is_dead = 0;
		pthread_mutex_init(&(data->philos[i].fork_l), NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (i == data->philo_nb - 1)
			data->philos[i].fork_r = &data->philos[0].fork_l;
		else
			data->philos[i].fork_r = &data->philos[i + 1].fork_l;
		i++;
	}
}

void	ft_display(t_philo *philo, int id_philo, char *action)
{
	check_dead(philo);

	if (philo->env->is_dead != 1)
	{
		pthread_mutex_lock(&(philo->env->display));
		printf("%s%lld%s Philo %d %s\n", YEL, (get_time_ms() - philo->start_t), RESET, id_philo, action);
		pthread_mutex_unlock(&(philo->env->display));
		printf("CE PHILO EST UN TROLLER %D\n mort a cause de %lld %lld\n", philo->id, philo->last_eat, philo->start_t);
	}
	else
	{
		printf("CE PHILO A ETE TROLLER %D\n", philo->id);
		pthread_mutex_lock(&(philo->env->display));
		printf("%s%lld%s Philo %d %s\n", RED, (get_time_ms() - philo->start_t), RESET, id_philo, action);
		pthread_mutex_unlock(&(philo->env->display));
	}
}


int	main(int argc, char **argv)
{
	t_env		*data;

	data = malloc(sizeof(t_env));
	check_arg(argc, argv, data);
	init_all_philo(data);
	create_philo(data);
	//destroy_forks(&data);
	return (0);
}
