/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/03 10:40:35 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		timems;

	gettimeofday(&time, NULL);
	timems = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (timems);
}

void	eat(t_philo *philo)
{
    sleep(1);
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
	t_philo philo;

	philo = *(t_philo *)arg;
	while(check_dead(&philo) != 0)
	{
		think(&philo);
		take_fork(philo.env, philo.id - 1);
		take_fork(philo.env, philo.id % philo.env->philo);
		eat(&philo);
		put_fork(philo.env, philo.id - 1);
		put_fork(philo.env, philo.id % philo.env->philo);
		check_dead(&philo);
	}
    printf("%lld philo %d have %d fork\n",(get_time_ms() - philo.start_t) , philo.id, philo.fork);
	return (NULL);
}

int	check_dead(t_philo *philo)
{
	if(philo->last_eat < philo->env->die)
	{
		dead_philo(philo);
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

void    destroy_forks(t_env *data)
{
    int i;

    i = 0;
    while ( i < data->philo)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
}

void	init_fork(t_env *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo);
	while (i < data->philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return ;
}

void	create_philo(t_env *data, t_philo *philo)
{
	int			i;
	long long s_t;

	s_t = get_time_ms();
    data->start_t = s_t;
	i = 0;
    init_fork(data);
	if (!data->forks)
		exit(1);
	while (i < data->philo)
	{
		philo[i].id = i + 1;
		philo[i].start_t = s_t;
		philo[i].env = data;
		philo[i].fork = 1;
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_env		data;
	t_philo		*philo;

	check_arg(argc, argv, &data);
	philo = malloc(sizeof(t_philo) * data.philo);
    if (!philo)
        return (1);
    create_philo(&data, philo);
    destroy_forks(&data);
	return (0);
}
