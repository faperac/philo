/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/12 15:42:47 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	long long time_eat;

	time_eat = get_time_ms() - philo->start_t;
	check_dead(philo);
	philo->last_eat = get_time_ms();
	ft_usleep(philo->env->eat, philo->env);
	pthread_mutex_lock(&(philo->env->display));
	printf("%s%lld%s Philo %d is eating\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	pthread_mutex_unlock(&(philo->env->display));
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	philo->nb_of_eat++;
	//printf("philo have %d fork", philo->fork);
	psleep(philo);
	think(philo);
	check_dead(philo);
}

void	psleep(t_philo *philo)
{
	ft_usleep(philo->env->sleep, philo->env);
	pthread_mutex_lock(&(philo->env->display));
	printf("%s%lld%s Philo %d is sleeping\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	pthread_mutex_unlock(&(philo->env->display));
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->display));
	printf("%s%lld%s Philo %d is thinking\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	pthread_mutex_unlock(&(philo->env->display));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep((philo->env->eat / 10), philo->env);
	while (1)
	{
		take_fork(philo);
		eat(philo);
	}
	//printf("%lld philo %d have %d fork\n",(get_time_ms() - philo->start_t) , philo->id);
	return (NULL);
}

int	check_dead(t_philo *philo)
{
	if (philo->last_eat < philo->env->eat && philo->nb_of_eat >= 1)
		dead_philo(philo);
		//exit program and stop all philo
	return (1);
}

void	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->display));
	printf("%lld Philo %d dead\n", (get_time_ms() - philo->start_t), philo->id);
	pthread_mutex_unlock(&(philo->env->display));
	exit(1);
}

void	take_fork(t_philo *philo)
{
	//check_dead(philo);
	pthread_mutex_lock(&(philo->fork_l));
	pthread_mutex_lock(&(philo->env->display));
	printf("%s%lld%s Philo %d has left taken a fork\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	pthread_mutex_unlock(&(philo->env->display));
	pthread_mutex_lock((philo->fork_r));
	pthread_mutex_lock(&(philo->env->display));
	printf("%s%lld%s Philo %d has right taken a fork\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	pthread_mutex_unlock(&(philo->env->display));
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
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_eat = 0;
		data->philos[i].nb_of_eat = 0;
		data->philos[i].start_t = s_t;
		data->philos[i].env = data;
		pthread_mutex_init(&(data->display), NULL);
		pthread_mutex_init(&(data->e_eat), NULL);
		pthread_mutex_init(&(data->s_eat), NULL);
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
