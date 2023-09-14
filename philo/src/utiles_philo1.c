/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_philo1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:41:16 by fabperei          #+#    #+#             */
/*   Updated: 2023/09/13 14:20:00 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	resultat;
	int	nbsigne;

	nbsigne = 1;
	i = 0;
	resultat = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		if (str[i] == '-')
			nbsigne = nbsigne * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		resultat = resultat * 10 + str[i] - '0';
		if (!(str[i] >= 48 && str[i] <= 57))
			return (resultat * nbsigne);
		i++;
	}
	return (resultat * nbsigne);
}

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_usleep(unsigned int ms)
{
	long int	time;

	time = get_time_ms();
	while (get_time_ms() - time < ms)
		usleep(ms / 10);
}

void	ft_display(t_philo *philo, int id_philo, char *action)
{
	long long	time;

	pthread_mutex_lock(&(philo->env->display));
	time = get_time_ms() - philo->env->start_time;
	if (!philo->env->one_dead && time >= 0 && !check_dead(philo, 0))
		printf("%s%lld%s Philo %d %s\n", YEL, get_time_ms() \
		- philo->env->start_time, RESET, id_philo, action);
	pthread_mutex_unlock(&(philo->env->display));
}

void	ft_free(t_env *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->philos[i].fork_l);
		pthread_mutex_destroy(data->philos[i].fork_r);
	}
	free(data->philos);
	pthread_mutex_destroy(&(data->display));
	pthread_mutex_destroy(&(data->dead_mutex));
	pthread_mutex_destroy(&(data->eat_mutex));
	pthread_mutex_destroy(&(data->stop));
}
