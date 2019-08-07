/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_specifier2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:00:50 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:51:20 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*type_s(char *res, va_list *ap)
{
	char	*s;
	int		len;

	s = va_arg(*ap, char*);
	if (s == NULL)
	{
		res = ft_strnew(6);
		ft_strcpy(res, "(null)");
		return (res);
	}
	len = (int)ft_strlen((char *)s);
	res = (char*)malloc((len + 1) * sizeof(char));
	ft_strcpy(res, s);
	return (res);
}

char	*type_p(char *res, va_list *ap, t_spec *spec)
{
	long	nb;
	char	*ret;
	int		len;

	nb = va_arg(*ap, long);
	res = ft_itoa_base(nb, 16, spec);
	len = (int)ft_strlen((char*)res);
	if (!(ret = ft_strnew(len + 2)))
		return (NULL);
	ft_strcpy(&ret[2], (char*)res);
	ret[0] = '0';
	ret[1] = 'x';
	free((char*)res);
	return (ret);
}

char	*type_f(char *res, va_list *ap, t_spec *spec)
{
	long double	nb;
	double		n;
	size_t		i;

	i = 0;
	if (spec->size[0] == 'L')
	{
		nb = va_arg(*ap, long double);
		res = ft_fitoa(nb, i);
	}
	else
	{
		n = va_arg(*ap, double);
		res = ft_fitoa(n, i);
	}
	return (res);
}

char	*type_id(char *res, va_list *ap, t_spec *spec)
{
	long long	nb;

	nb = va_arg(*ap, long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_itoa_base((char)nb, 10, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_itoa_base((short int)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_itoa_base((long long)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_itoa_base((long long)nb, 10, spec);
	else
		res = ft_itoa((int)nb);
	return (res);
}
