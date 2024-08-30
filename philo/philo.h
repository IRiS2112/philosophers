/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:58:49 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/22 13:01:15 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	t_data			*data;
	t_fork			*l_fork;
	t_fork			*r_fork;
	size_t			philo_id;
	size_t			last_meal;
	size_t			last_sleep;
	size_t			last_think;
	pthread_mutex_t	philo_lock;
	pthread_t		philosopher;
	size_t			last_r_fork;
	size_t			last_l_fork;
	long			num_of_meals;
}					t_philo;

struct s_data
{
	size_t			time_to_sleep;
	size_t			num_of_philo;
	size_t			time_to_eat;
	size_t			time_to_die;
	long			limit_meals;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	data_lock;
	size_t			starting;
	t_philo			*philo;
	t_fork			*fork;
	int				out;
	int				in;
};

size_t		get_current_time(void);
int			ft_check_var(t_data *data);
int			ft_usleep(size_t milliseconds, t_data *data);
void		ft_print(char *str, t_philo *philo, size_t time);

int			get_data(t_data *data, char **av);
int			ft_mutex_destroy(t_data	*data);

void		ft_putendl_fd(char *s, int fd);

int			ft_check(int ac, char **av);
long long	ft_atol(char *str);

void		*check_death(t_data *data);

int			routine(t_data *data);

#endif