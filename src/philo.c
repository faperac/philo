/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:52 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/02 15:55:15 by fabperei         ###   ########.fr       */
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
	usleep(400);
	printf("%lld and %lld\n",get_time_ms(), philo->start_t);
	//printf("%lld Philo %d is eating\n", (get_time_ms() - philo->start_t), philo->id);
	usleep(4000);
}

void	*philo_routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	philo.fork = 1;
	eat(&philo);
	//printf("time : %lld || philo %d created || philo have %d fork\n" , (get_time_ms() - philo.start_t), philo.id, philo.fork);
	return (NULL);	
}

void	create_philo(t_env *data, t_philo *philo)
{
	int			i;
	long long s_t;

	s_t = get_time_ms();
	i = 0;
	while (i < data->philo)
	{
		philo[i].id = i + 1;
		philo[i].start_t = s_t;
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while ( i < data->philo)
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
	if(!philo)
		return (1);
	create_philo(&data, philo);
	return (0);
}
