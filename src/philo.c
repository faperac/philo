/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/11 16:00:24 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	long long time_eat;

	time_eat = get_time_ms() - philo->start_t;
	printf("%s%lld%s Philo %d is eating\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	philo->nb_of_eat++;
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	usleep(philo->env->eat);
	//printf("philo have %d fork", philo->fork);
	philo->last_eat = get_time_ms();
	psleep(philo);
	think(philo);
}

void	psleep(t_philo *philo)
{
	printf("%s%lld%s Philo %d is sleeping\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	usleep(philo->env->sleep);
}

void	think(t_philo *philo)
{
	printf("%s%lld%s Philo %d is thinking\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(philo->env->eat / 10);
	while (1)
	{
		check_dead(philo);
		take_fork(philo);
		check_dead(philo);
		eat(philo);
		check_dead(philo);
	}
	//printf("%lld philo %d have %d fork\n",(get_time_ms() - philo->start_t) , philo->id);
	return (NULL);
}

int	check_dead(t_philo *philo)
{
	//pthread_mutex_lock((philo->env->eat));
	//pthread_mutex_lock((philo->last_eat));
	if (philo->last_eat < philo->env->eat && philo->nb_of_eat >= 1)
		dead_philo(philo);
		//exit program and stop all philo
	//pthread_mutex_unlock((philo->env->eat));
	//pthread_mutex_unlock((philo->last_eat));
	return (1);
}

void	dead_philo(t_philo *philo)
{
	printf("%lld Philo %d dead\n", (get_time_ms() - philo->start_t), philo->id);
	exit(1);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&(philo->fork_l));
		printf("%s%lld%s Philo %d has taken a fork\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
		pthread_mutex_lock((philo->fork_r));
		printf("%s%lld%s Philo %d has taken a fork\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	}
	else
	{
		usleep(5);
		pthread_mutex_lock(&(philo->fork_l));
		printf("%s%lld%s Philo %d has taken a fork\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
		pthread_mutex_lock((philo->fork_r));
		printf("%s%lld%s Philo %d has taken a fork\n", YEL, (get_time_ms() - philo->start_t), RESET, philo->id);
	}
	//pthread_mutex_lock(&data->forks[fork_i]);
	return ;
}

void	create_philo(t_env *data)
{
	int			i;
	long long	s_t;

	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		exit(EXIT_FAILURE);
	s_t = get_time_ms();
	data->start_t = s_t;
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_eat = 0;
		data->philos[i].nb_of_eat = 0;
		data->philos[i].start_t = s_t;
		data->philos[i].env = data;
		pthread_mutex_init(&(data->philos[i].fork_l), NULL);
		if (i == data->philo_nb - 1)
			data->philos[i].fork_r = &data->philos[0].fork_l;
		else
			data->philos[i].fork_r = &data->philos[i + 1].fork_l;
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

int	main(int argc, char **argv)
{
	t_env		*data;

	data = malloc(sizeof(t_env));
	check_arg(argc, argv, data);
	create_philo(data);
	//destroy_forks(&data);
	return (0);
}
