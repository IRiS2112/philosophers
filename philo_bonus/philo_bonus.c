/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:17:29 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/22 13:01:37 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	dinner(t_data *data)
{
	data->philo->last_r_fork = get_current_time() - data->starting;
	ft_print("has taken a fork", data->philo, data->philo->last_r_fork);
	ft_usleep(data->time_to_die);
	printf("%zu\t%zu\t%s\n", get_current_time() - data->starting,
		data->philo->philo_id, "died");
	free(data->philo);
	exit (0);
}

static int	one_routine(t_data *data)
{
	data->starting = get_current_time();
	data->philo->id = fork();
	if (data->philo->id == -1)
		return (ft_putendl_fd("ERROR : fork", 2), 1);
	if (!data->philo->id)
		dinner(data);
	wait(NULL);
	ft_sem_close(data);
	free(data->philo);
	exit (0);
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
			ft_sem_close(&data);
			return (free(data.philo), 1);
		}
		else if (data.num_of_philo > 1 && routine(&data))
		{
			ft_sem_close(&data);
			return (free(data.philo), 1);
		}
		if (ft_sem_close(&data))
			return (free(data.philo), 1);
		return (free(data.philo), 0);
	}
	return (ft_putendl_fd("Wrong input!", 2), 1);
}
