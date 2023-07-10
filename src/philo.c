/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/10 15:15:46 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	printf("philo have %d fork", philo->fork);
	philo->last_eat = get_time_ms();
	printf("%lld Philo %d is eating\n", (get_time_ms() - philo->start_t), philo->id);
}

void	think(t_philo *philo)
{
	printf("%lld Philo %d is thinking\n", (get_time_ms() - philo->start_t), philo->id);
	sleep(1);
}

void	*philo_routine(void *arg)
{
	t_env *data;

	data = *(t_env *)arg;
	while (!check_dead(&data->philos))
	{
		think(&philo);
		//give_fork(&philo);
		take_fork(philo.env, philo.id - 1);
		take_fork(philo.env, philo.id % philo.env->philo);
		eat(&philo);
		put_fork(philo.env, philo.id - 1);
		put_fork(philo.env, philo.id % philo.env->philo);
		if (check_dead(&philo))
			exit(EXIT_FAILURE);
	}
	printf("%lld philo %d have %d fork\n",(get_time_ms() - data.start_t) , philo.id, philo.fork);
	return (NULL);
}

int	check_dead(t_philo *philo)
{
	if (philo->last_eat < philo->env->die)
	{
		dead_philo(philo);
		//exit program and stop all philo
		return (1);
	}
	return (0);
}

void	dead_philo(t_philo *philo)
{
	printf("%lld Philo %d dead\n", (get_time_ms() - philo->start_t), philo->id);
	exit(1);
}

void	take_fork(t_env *data, int fork_i)
{
	printf("%lld Philo %d has taken a fork\n", (get_time_ms() - data->start_t), fork_i);
	printf("Philo have %d fork\n", fork_i);
	pthread_mutex_lock(&data->forks[fork_i]);
	return ;
}

void	give_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		philo->fork++;
	if (philo->fork == 2)
		eat(philo);
}
void	put_fork(t_env *data, int fork_i)
{
	pthread_mutex_unlock(&data->forks[fork_i]);
	return ;
}

void	destroy_forks(t_env *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	init_fork(t_env *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return ;
}

void	create_philo(t_env *data)
{
	int			i;
	long long	s_t;

	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (1);
	s_t = get_time_ms();
	data->start_t = s_t;
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].start_t = s_t;
		data->philos[i].env = data;
		data->philos[i].fork = 0;
		pthread_create(data->philos[i].thread, NULL, philo_routine, &data);
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_env		*data;

	data = malloc(sizeof(t_env));
	check_arg(argc, argv, data);
	create_philo(data);
	//destroy_forks(&data);
	return (0);
}
