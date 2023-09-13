/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabperei <fabperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:18:44 by fabperei          #+#    #+#             */
/*   Updated: 2023/09/12 11:36:02 by fabperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\e[0m"

# define FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DIED		"died"

typedef struct s_philo
{
	int				id;
	int				nb_of_eat;
	int				is_eating;
	pthread_t		thread;
	long long		last_eat;
	struct s_env	*env;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
}t_philo;

typedef struct s_env
{
	int				philo_nb;
	int				die;
	int				eat;
	int				sleep;
	int				nb_eat;
	t_philo			*philos;
	int				one_dead;
	long long		start_time;
	pthread_mutex_t	display;
	pthread_mutex_t	stop;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
}t_env;

int			check_arg(int argc, char **argv);
int			check_only_number(char **argv);
t_env		*ft_init_arg(char **argv, t_env *data);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long long	get_time_ms(void);
void		ft_display(t_philo *philo, int id_philo, char *action);
void		ft_usleep(unsigned int time);
void		create_philo(t_env *data);
int			init_all_philo(t_env *data);
void		*philo_routine(void *arg);
void		take_fork(t_philo *philo);
void		eat_spleet_think(t_philo *philo);
int			check_dead(t_philo *philo, int nb);
void		*dead_philo(void *arg);
int			ft_error(char *msg);
void		ft_free(t_env *data);
#endif
