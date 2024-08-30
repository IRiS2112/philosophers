/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:19:53 by hakaraou          #+#    #+#             */
/*   Updated: 2024/04/15 11:38:18 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&(philo->philo_lock));
	time = get_current_time() - philo->data->starting - philo->last_meal;
	pthread_mutex_unlock(&(philo->philo_lock));
	if (time > philo->data->time_to_die)
		return (1);
	return (0);
}

void	*check_death(t_data *data)
{
	size_t	i;

	while (!ft_check_var(data))
	{
		i = -1;
		while (++i < data->num_of_philo && !ft_check_var(data))
		{
			if (dead(data->philo + i))
			{
				pthread_mutex_lock(&(data->data_lock));
				data->out = 1;
				pthread_mutex_unlock(&(data->data_lock));
				pthread_mutex_lock(&(data->write_lock));
				printf("%zu\t%zu\t%s\n", get_current_time() - data->starting,
					data->philo[i].philo_id, "died");
				pthread_mutex_unlock(&(data->write_lock));
				return (NULL);
			}
		}
	}
	return (NULL);
}
