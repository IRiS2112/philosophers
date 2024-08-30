/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:35:45 by hakaraou          #+#    #+#             */
/*   Updated: 2024/05/22 13:01:06 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd == -1)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "ERROR : gettimeofday()\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds && !ft_check_var(data))
		usleep(1);
	return (0);
}

int	ft_check_var(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->data_lock));
	i = data->out;
	pthread_mutex_unlock(&(data->data_lock));
	return (i);
}

void	ft_print(char *str, t_philo *philo, size_t time)
{
	pthread_mutex_lock(&(philo->data->write_lock));
	if (!ft_check_var(philo->data))
		printf("%zu\t%zu\t%s\n", time, philo->philo_id, str);
	pthread_mutex_unlock(&(philo->data->write_lock));
}
