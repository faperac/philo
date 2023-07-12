/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:18:44 by fabperei          #+#    #+#             */
/*   Updated: 2023/07/12 15:43:21 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\e[0m"

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long long			start_t;
	long long			last_eat;
	int					nb_of_eat;
	struct s_env		*env;
	pthread_mutex_t		fork_l;
	pthread_mutex_t		*fork_r;
}t_philo;

typedef struct s_env
{
	int				philo_nb;
	int				die;
	int				eat;
	int				sleep;
	int				nb_eat;
	long long		start_t;
	t_philo			*philos;
	pthread_mutex_t		e_eat;
	pthread_mutex_t		s_eat;
	pthread_mutex_t		display;
}t_env;

// ft_utils
void		check_arg(int argc, char **argv, t_env *data);
void		check_only_number(char **argv);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long long	get_time_ms(void);
void		ft_usleep(unsigned int time, t_env *data);
// philo
void		create_philo(t_env *data);
void		init_all_philo(t_env *data);
void		*philo_routine(void *arg);
void		take_fork(t_philo *philo);
void		think(t_philo *philo);
void		eat(t_philo *philo);
void		psleep(t_philo *philo);
int			check_dead(t_philo *philo);
void		dead_philo(t_philo *philo);

#endif
