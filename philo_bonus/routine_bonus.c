/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:34:12 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/22 12:59:46 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eats(t_philo *philo)
{
	sem_wait((philo->data->fork_lock));
	philo->last_r_fork = get_current_time() - philo->data->starting;
	ft_print("has taken a fork", philo, philo->last_r_fork);
	sem_wait((philo->data->fork_lock));
	philo->last_l_fork = get_current_time() - philo->data->starting;
	ft_print("has taken a fork", philo, philo->last_l_fork);
	sem_wait((philo->philo_lock));
	philo->last_meal = get_current_time() - philo->data->starting;
	sem_post((philo->philo_lock));
	ft_print("is eating", philo, philo->last_meal);
	ft_usleep(philo->data->time_to_eat);
	sem_post((philo->data->fork_lock));
	sem_post((philo->data->fork_lock));
	philo->num_of_meals++;
}

static int	ft_dead(t_philo *philo)
{
	size_t	time;

	sem_wait((philo->philo_lock));
	time = get_current_time() - philo->data->starting - philo->last_meal;
	sem_post((philo->philo_lock));
	if (time > philo->data->time_to_die)
		return (1);
	return (0);
}

static void	*ft_checker(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (1)
	{
		if (ft_dead(philo))
		{
			sem_wait((philo->data->write_lock));
			printf("%zu\t%zu\t%s\n", get_current_time() - philo->data->starting,
				philo->philo_id, "died");
			break ;
		}
	}
	exit (30);
}

static void	*ft_routine(t_philo *philo)
{
	pthread_create(&(philo->checker), NULL, &ft_checker, (void *)philo);
	while (1)
	{
		philo_eats(philo);
		if ((philo->data->limit_meals != -1
				&& philo->num_of_meals > philo->data->limit_meals))
			exit (0);
		philo->last_sleep = get_current_time() - philo->data->starting;
		ft_print("is sleeping", philo, philo->last_sleep);
		ft_usleep(philo->data->time_to_sleep);
		philo->last_think = get_current_time() - philo->data->starting;
		ft_print("is thinking", philo, philo->last_think);
	}
	pthread_detach(philo->checker);
	return (NULL);
}

int	routine(t_data *data)
{
	size_t	i;
	int		status;

	i = -1;
	data->starting = get_current_time();
	while (++i < data->num_of_philo)
	{
		data->philo[i].id = fork();
		if (data->philo[i].id == -1)
			return (ft_putendl_fd("ERROR! : fork", 2), 1);
		if (!data->philo[i].id)
			ft_routine(&data->philo[i]);
	}
	while (1)
	{
		if (waitpid(-1, &status, WNOHANG) == -1)
			break ;
		if (WEXITSTATUS(status) == 30)
		{
			i = -1;
			while (++i < data->num_of_philo)
				kill(data->philo[i].id, SIGKILL);
		}
	}
	return (0);
}
