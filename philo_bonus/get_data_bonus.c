/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:23:22 by hakaraou          #+#    #+#             */
/*   Updated: 2024/04/18 18:41:55 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_sem_close(t_data	*data)
{
	size_t	i;
	char	*name;
	char	*name1;

	sem_close(data->fork_lock);
	sem_unlink("/fork_sem");
	sem_close(data->write_lock);
	sem_unlink("/write_sem");
	i = -1;
	while (++i < data->num_of_philo)
	{
		name1 = ft_itoa(data->philo[i].philo_id);
		if (!name1)
			return (ft_putendl_fd("ERROR : get_name1", 2), 1);
		sem_close(data->philo[i].philo_lock);
		name = ft_strjoin("/", name1);
		free(name1);
		if (!name)
			return (ft_putendl_fd("ERROR : get_name", 2), 1);
		sem_unlink(name);
		free (name);
	}
	return (0);
}

static int	get_philo(t_data *data)
{
	size_t	i;
	char	*name;
	char	*name1;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].num_of_meals = 0;
		data->philo[i].data = data;
		name1 = ft_itoa(data->philo[i].philo_id);
		if (!name1)
			return (ft_putendl_fd("ERROR : get_name1", 2), 1);
		name = ft_strjoin("/", name1);
		free(name1);
		if (!name)
			return (ft_putendl_fd("ERROR : get_name", 2), 1);
		sem_unlink(name);
		data->philo[i].philo_lock = sem_open(name, O_CREAT, 0600, 1);
		if (data->philo[i].philo_lock == SEM_FAILED)
			return (free (name), ft_putendl_fd("ERROR : open_philo_sem", 2), 1);
		free(name);
		i++;
	}
	return (0);
}

static int	ft_sem(t_data	*data)
{
	sem_unlink("/write_sem");
	sem_unlink("/fork_sem");
	data->write_lock = sem_open("/write_sem", O_CREAT, 0600, 1);
	if (data->write_lock == SEM_FAILED)
		return (ft_putendl_fd("ERROR : open_write_sem", 2), 1);
	data->fork_lock = sem_open("/fork_sem", O_CREAT, 0600, data->num_of_philo);
	if (data->fork_lock == SEM_FAILED)
		return (ft_putendl_fd("ERROR : open_fork_sem", 2), 1);
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
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (ft_putendl_fd("ERROR : malloc_philo", 2), 1);
	get_philo(data);
	if (ft_sem(data))
		return (1);
	return (0);
}
