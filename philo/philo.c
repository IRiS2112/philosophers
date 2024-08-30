/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:55:44 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/22 12:44:52 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner(void *v_data)
{
	t_data	*data;

	data = (t_data *)v_data;
	data->philo->last_r_fork = get_current_time() - data->starting;
	ft_print("has taken a fork", data->philo, data->philo->last_r_fork);
	ft_usleep(data->time_to_die, data);
	printf("%zu\t%zu\t%s\n", get_current_time() - data->starting,
		data->philo->philo_id, "died");
	return (NULL);
}

static int	one_routine(t_data *data)
{
	data->starting = get_current_time();
	if (pthread_create(&data->philo->philosopher, NULL, &dinner,
			(void *)data) != 0)
		return (ft_putendl_fd("ERROR : creating_philo_thread", 2), 1);
	if (pthread_join(data->philo->philosopher, NULL) != 0)
		return (ft_putendl_fd("ERROR : joining_philo_thread", 2), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac == 5 || ac == 6))
	{
		if (ft_check(ac, av) || get_data(&data, av))
			return (1);
		if (data.num_of_philo == 1 && one_routine(&data))
		{
			ft_mutex_destroy(&data);
			return (free(data.philo), free(data.fork), 1);
		}
		else if (data.num_of_philo > 1 && routine(&data))
		{
			ft_mutex_destroy(&data);
			return (free(data.philo), free(data.fork), 1);
		}
		if (ft_mutex_destroy(&data))
			return (free(data.philo), free(data.fork), 1);
		return (free(data.philo), free(data.fork), 0);
	}
	return (ft_putendl_fd("Wrong input!", 2), 1);
}
