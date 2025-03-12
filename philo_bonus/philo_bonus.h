/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:13:28 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/22 13:00:32 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	long			num_of_meals;
	sem_t			*philo_lock;
	size_t			last_l_fork;
	size_t			last_r_fork;
	size_t			last_sleep;
	size_t			last_think;
	size_t			last_meal;
	size_t			philo_id;
	pthread_t		checker;
	t_data			*data;
	pid_t			id;
}					t_philo;

struct s_data
{
	t_philo			*philo;
	size_t			starting;
	sem_t			*fork_lock;
	sem_t			*write_lock;
	long			limit_meals;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			num_of_philo;
	size_t			time_to_sleep;
};

void		ft_print(char *str, t_philo *philo, size_t time);
int			ft_usleep(size_t milliseconds);
size_t		get_current_time(void);

int			ft_sem_close(t_data	*data);
int			get_data(t_data *data, char **av);

char		*ft_strjoin(char *s1, char *s2);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);

long long	ft_atol(char *str);
int			ft_check(int ac, char **av);

int			routine(t_data *data);

#endif