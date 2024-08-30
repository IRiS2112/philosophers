/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:41:42 by hakaraou          #+#    #+#             */
/*   Updated: 2024/04/16 15:42:08 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	len_n(int n)
{
	size_t	i;

	i = 0;
	if (n < 1)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*str_n(int len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	return (str);
}

static int	pos_n(int n)
{
	int	pn;

	pn = 1;
	if (n > 0)
		pn *= n;
	else
		pn *= -n;
	return (pn);
}

char	*ft_itoa(int n)
{
	int				len;
	int				s;
	char			*str;
	unsigned int	pn;

	len = len_n(n);
	str = str_n(len);
	if (!str)
		return (0);
	str[len] = 0;
	pn = pos_n(n);
	while (len--)
	{
		str[len] = 48 + (pn % 10);
		pn /= 10;
	}
	s = 0;
	if (n < 0)
		s = 1;
	if (s)
		*(str) = 45;
	return (str);
}
