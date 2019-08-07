/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:54:16 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 16:01:10 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_digits(long double num)
{
	size_t		i;
	long long	n;

	n = (int)num;
	i = 0;
	if (num == 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static size_t	dig_after_dot(long double *num, size_t *zero_count)
{
	size_t		count;
	long long	n;
	long double	nb;

	count = 0;
	*zero_count = 0;
	n = (int)(*num);
	if (n == 0)
		(*zero_count)++;
	nb = n;
	while (nb < *num && count < 6)
	{
		*num *= 10;
		n = (int)(*num);
		if (n == 0)
			(*zero_count)++;
		nb = n;
		count++;
	}
	return (count);
}

char			*ft_fitoa(long double num, size_t i)
{
	long double nb;
	size_t		dig;
	size_t		zero_count;
	long long	n;
	char		*str;

	nb = num;
	if (num < 0)
		nb *= -1;
	dig = dig_after_dot(&nb, &zero_count);
	n = (int)nb;
	i = ft_digits(nb) + 1 + zero_count;
	if (num < 0)
		i++;
	str = ft_fitoa2(num, i, dig, n);
	return (str);
}

char			*ft_fitoa2(long double num, size_t i, size_t dig, long long n)
{
	char		*str;
	size_t		tmp;

	tmp = i;
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i-- > 0)
	{
		if (num < 0 && i == 0)
			str[i] = '-';
		if (i == tmp - dig - 1)
		{
			str[i] = '.';
			i--;
		}
		if (n == 0)
			str[i] = '0';
		else
		{
			str[i] = n % 10 + '0';
			n /= 10;
		}
	}
	return (str);
}
