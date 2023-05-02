/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:18:44 by fabperei          #+#    #+#             */
/*   Updated: 2023/05/02 15:03:38 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long long	start_t;
	int			fork;
}t_philo;


typedef struct s_env
{
	int			philo;
	int			die;
	int			eat;
	int			sleep;
	int			nb_eat;
}t_env;


void	check_arg(int argc, char **argv, t_env *data);
int		ft_atoi(const char *str);
void	create_philo(t_env *data, t_philo *philo);
void	*philo_routine(void *arg);

#endif