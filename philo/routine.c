/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:04:39 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/21 20:38:28 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&(philo->l_fork->fork));
	philo->last_r_fork = get_current_time() - philo->data->starting;
	ft_print("has taken a fork", philo, philo->last_r_fork);
	pthread_mutex_lock(&(philo->r_fork->fork));
	philo->last_l_fork = get_current_time() - philo->data->starting;
	ft_print("has taken a fork", philo, philo->last_l_fork);
	pthread_mutex_lock(&(philo->philo_lock));
	philo->last_meal = get_current_time() - philo->data->starting;
	pthread_mutex_unlock(&(philo->philo_lock));
	ft_print("is eating", philo, philo->last_meal);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(&(philo->l_fork->fork));
	pthread_mutex_unlock(&(philo->r_fork->fork));
	pthread_mutex_lock(&(philo->philo_lock));
	philo->num_of_meals++;
	pthread_mutex_unlock(&(philo->philo_lock));
}

void	all_started(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->data_lock));
		i = philo->data->in;
		pthread_mutex_unlock(&(philo->data->data_lock));
		if (i == 1)
			break ;
	}
}

static void	*ft_routine(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	all_started(philo);
	if (philo->philo_id % 2)
		ft_usleep(philo->data->time_to_eat, philo->data);
	while (!ft_check_var(philo->data))
	{
		philo_eats(philo);
		if (philo->data->limit_meals != -1
			&& philo->num_of_meals > philo->data->limit_meals)
			return (pthread_mutex_lock(&(philo->data->data_lock)),
				philo->data->out = 1,
				pthread_mutex_unlock(&(philo->data->data_lock)), NULL);
		pthread_mutex_lock(&(philo->philo_lock));
		philo->last_sleep = get_current_time() - philo->data->starting;
		ft_print("is sleeping", philo, philo->last_sleep);
		pthread_mutex_unlock(&(philo->philo_lock));
		ft_usleep(philo->data->time_to_sleep, philo->data);
		pthread_mutex_lock(&(philo->philo_lock));
		philo->last_think = get_current_time() - philo->data->starting;
		ft_print("is thinking", philo, philo->last_think);
		pthread_mutex_unlock(&(philo->philo_lock));
	}
	return (NULL);
}

int	routine(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&(data->philo[i].philosopher), NULL,
				&ft_routine, &(data->philo[i])) != 0)
			return (ft_putendl_fd("ERROR : creating_philo_thread", 2), 1);
	}
	data->starting = get_current_time();
	pthread_mutex_lock(&(data->data_lock));
	data->in = 1;
	pthread_mutex_unlock(&(data->data_lock));
	check_death(data);
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->philo[i].philosopher, NULL) != 0)
			return (ft_putendl_fd("ERROR : joining_philo_thread", 2), 1);
	}
	return (0);
}
