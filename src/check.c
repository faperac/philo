/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:16:36 by fabperei          #+#    #+#             */
/*   Updated: 2023/09/12 12:17:10 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->env->dead_mutex);
	if (nb)
		philo->env->one_dead = 1;
	if (philo->env->one_dead)
	{
		pthread_mutex_unlock(&philo->env->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->env->dead_mutex);
	return (0);
}

void	*dead_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(philo->env->die + 1);
	pthread_mutex_lock(&philo->env->eat_mutex);
	pthread_mutex_lock(&philo->env->stop);
	if (!check_dead(philo, 0) && get_time_ms() - \
		philo->last_eat >= philo->env->die)
	{
		pthread_mutex_unlock(&philo->env->eat_mutex);
		pthread_mutex_unlock(&philo->env->stop);
		ft_display(philo, philo->id, DIED);
		check_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->env->eat_mutex);
	pthread_mutex_unlock(&philo->env->stop);
	return (NULL);
}
