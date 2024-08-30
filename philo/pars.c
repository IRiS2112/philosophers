/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:58:03 by hakaraou          #+#    #+#             */
/*   Updated: 2024/04/18 15:35:33 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atol(char *str)
{
	long long	c;
	int			sign;

	while ((*str != '\0')
		&& ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	sign = 1;
	if ((*str != '\0')
		&& (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	c = 0;
	while ((*str != '\0')
		&& (*str >= '0' && *str <= '9'))
	{
		c = c * 10 + (*str - '0');
		str++;
	}
	return (c * sign);
}

static int	check_space(char *av)
{
	size_t	j;
	size_t	k;

	k = 0;
	j = 0;
	while (av[j])
		j++;
	while (av[k] && (av[k] == '\t' || av[k] == '\n'
			|| av[k] == ' ' || av[k] == '\v'
			|| av[k] == '\f' || av[k] == '\r'))
		k++;
	return (1 * (j == 0 || k == j));
}

static int	check_int(char *av)
{
	int	i;

	i = 0;
	while (av[i] == ' ')
		i++;
	if (av[i] == '-' || av[i] == '+')
		i++;
	if (!av[i] || av[i] < '0' || av[i] > '9')
		return (1);
	while (av[i] && av[i] != ' ')
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	while (av[i] && av[i] != ' ')
		i++;
	while (av[i + 1] && av[i] == ' ')
	{
		i++;
		if (av[i] != ' ')
			return (1);
	}
	return (0);
}

int	ft_check(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (check_space(av[i]) || check_int(av[i]))
			return (ft_putendl_fd("The value is not digit!", 2), 1);
	}
	if (ft_atol(av[1]) > 200)
		return (ft_putendl_fd("Too many philosophers!", 2), 1);
	if (ft_atol(av[2]) < 60 || ft_atol(av[3]) < 60 || ft_atol(av[4]) < 60)
		return (ft_putendl_fd("Not enough time!", 2), 1);
	i = 0;
	while (++i < ac)
	{
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < 0)
			return (ft_putendl_fd("The value is too big or negative!", 2), 1);
	}
	if (ac == 6)
	{
		if (ft_atol(av[ac - 1]) == 0)
			return (ft_putendl_fd("No meal!", 2), 1);
	}
	return (0);
}
