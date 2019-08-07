/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:55:30 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 17:18:37 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_digits(long long num, int base)
{
	size_t		i;

	i = 0;
	if (num == 0)
		i = 1;
	while (num)
	{
		num /= base;
		i++;
	}
	return (i);
}

char			*ft_itoa_base(long long num, int base, t_spec *spec)
{
	char		*str;
	long long	nb;
	size_t		i;

	nb = num;
	if (ft_itoa_base2(num, base, &str, &i))
		return (str);
	if (num < 0)
		nb *= -1;
	while (i-- > 0)
	{
		if (num < 0 && i == 0 && base == 10)
			str[i] = '-';
		else if (nb % base < 10)
			str[i] = nb % base + '0';
		else if (spec->type == 'X')
			str[i] = nb % base + 55;
		else
			str[i] = nb % base + 87;
		nb /= base;
	}
	return (str);
}

int				ft_itoa_base2(long long num, int base, char **str, size_t *i)
{
	if (num == -9223372036854775807 - 1)
	{
		if (!(str[0] = ft_strnew(20)))
		{
			str[0] = NULL;
			return (1);
		}
		ft_strcpy(str[0], "-9223372036854775808");
		return (1);
	}
	*i = ft_digits(num, base);
	if (num < 0 && base == 10)
		(*i)++;
	if (!(str[0] = ft_strnew(*i)))
	{
		str[0] = NULL;
		return (1);
	}
	return (0);
}
