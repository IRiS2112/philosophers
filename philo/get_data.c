/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:57:25 by hakaraou          #+#    #+#             */
/*   Updated: 2024/04/17 14:40:41 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mutex_destroy(t_data	*data)
{
	size_t	i;

	i = 0;
	if (pthread_mutex_destroy(&(data->data_lock)) != 0)
		return (ft_putendl_fd("ERROR : destroy_mutex_data", 2), 1);
	if (pthread_mutex_destroy(&(data->philo->philo_lock)) != 0)
		return (ft_putendl_fd("ERROR : destroy_mutex_philo", 2), 1);
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&(data->fork[i].fork)) != 0)
			return (ft_putendl_fd("ERROR : destroy_mutex_fork", 2), 1);
		i++;
	}
	if (pthread_mutex_destroy(&(data->write_lock)) != 0)
		return (ft_putendl_fd("ERROR : destroy_mutex_write", 2), 1);
	return (0);
}

static int	get_fork(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&(data->fork[i].fork), NULL) != 0)
			return (ft_putendl_fd("ERROR : mutex_fork", 2), 1);
		i++;
	}
	return (0);
}

static int	get_philo(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&(data->philo[i].philo_lock), NULL) != 0)
			return (ft_putendl_fd("ERROR : mutex_philo_lock", 2), 1);
		data->philo[i].philo_id = i + 1;
		data->philo[i].num_of_meals = 0;
		data->philo[i].data = data;
		data->philo[i].r_fork = data->fork + i;
		if (i == data->num_of_philo - 1)
			data->philo[i].l_fork = data->fork;
		else
			data->philo[i].l_fork = data->fork + i + 1;
		i++;
	}
	return (0);
}

static int	ft_mutex(t_data	*data)
{
	if (pthread_mutex_init(&(data->write_lock), NULL) != 0)
		return (ft_putendl_fd("ERROR : mutex_write_lock", 2), 1);
	if (pthread_mutex_init(&(data->data_lock), NULL) != 0)
		return (ft_putendl_fd("ERROR : mutex_in_lock", 2), 1);
	return (0);
}

int	get_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->limit_meals = ft_atol(av[5]);
	else
		data->limit_meals = -1;
	data->in = 0;
	data->out = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (ft_putendl_fd("ERROR : malloc_philo", 2), 1);
	data->fork = malloc(sizeof(t_fork) * data->num_of_philo);
	if (!data->fork)
		return (ft_putendl_fd("ERROR : malloc_fork", 2), free(data->philo), 1);
	if (get_fork(data) || get_philo(data) || ft_mutex(data))
		return (free(data->philo), free(data->fork), 1);
	return (0);
}
