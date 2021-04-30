/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yekim <yekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 06:56:38 by yekim             #+#    #+#             */
/*   Updated: 2021/05/01 07:03:58 by yekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

size_t
	ft_strlen(const char *str)
{
	size_t	ret;

	ret = 0;
	while (*(str++))
		++ret;
	return (ret);
}

int
	ft_atoi(const char *nptr)
{
	long long	ret;
	int			sign;

	if (nptr == NULL)
		return (0);
	sign = 0;
	while (*nptr == '\f' || *nptr == '\n' || *nptr == '\r'
			|| *nptr == '\t' || *nptr == '\v' || *nptr == ' ')
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			++sign;
		++nptr;
	}
	ret = 0;
	while (*nptr >= 48 && *nptr <= 57)
		ret = ret * 10 + (long long)(*(nptr++) - '0');
	ret = sign % 2 == 0 ? ret : -ret;
	return ((int)ret);
}

size_t
	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	ret;
	size_t	len_src;

	ret = 0;
	if (src == NULL)
		return (ret);
	len_src = ft_strlen(src);
	if (dest == NULL || size == 0)
		return (len_src);
	while (ret < len_src && ret < size - 1)
	{
		dest[ret] = src[ret];
		++ret;
	}
	dest[ret] = '\0';
	return (len_src);
}

void
	gen_name_tag(
	char *name,
	char *type,
	int nbr)
{
	int	idx;

	idx = ft_strlcpy(name, type, ft_strlen(type) + 1);
	if (nbr < 10)
	{
		name[idx++] = '0';
		name[idx++] = '0';
		name[idx++] = nbr + '0';
	}
	else if (nbr < 100)
	{
		name[idx++] = '0';
		name[idx++] = nbr / 10 + '0';
		name[idx++] = nbr % 10 + '0';
	}
	else if (nbr < 1000)
	{
		name[idx++] = nbr / 100 + '0';
		name[idx++] = nbr % 100 / 10 + '0';
		name[idx++] = nbr % 100 % 10 + '0';
	}
	name[idx] = '\0';
}
