/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:23:44 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 16:44:43 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*type_specifier(t_spec *spec, va_list *ap)
{
	char	*res;

	res = NULL;
	if (spec->type == 'c')
		res = type_c(res, ap);
	else if (spec->type == 's')
		res = type_s(res, ap);
	else if (spec->type == 'p')
		res = type_p(res, ap, spec);
	else if (spec->type == 'o'
			|| spec->type == 'x' || spec->type == 'X')
		res = type_ox_bigx(res, spec, ap);
	else if (spec->type == 'f')
		res = type_f(res, ap, spec);
	else if (spec->type == 'i' || spec->type == 'd')
		res = type_id(res, ap, spec);
	else if (spec->type == '%')
		res = type_percent(res);
	else if (spec->type == 'u')
		res = type_u(res, ap, spec);
	return (res);
}

char	*type_percent(char *res)
{
	res = (char*)malloc(2 * sizeof(char));
	res[0] = '%';
	res[1] = '\0';
	return (res);
}

char	*type_u(char *res, va_list *ap, t_spec *spec)
{
	unsigned long long	nb;

	nb = va_arg(*ap, unsigned long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_uitoa_base((unsigned char)nb, 10, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_uitoa_base((unsigned short int)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_uitoa_base((unsigned long long)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_uitoa_base((unsigned long long)nb, 10, spec);
	else
		res = ft_uitoa_base((unsigned int)nb, 10, spec);
	return (res);
}

char	*type_ox_bigx(char *res, t_spec *spec, va_list *ap)
{
	unsigned long long	nb;
	int					base;

	if (spec->type == 'o')
		base = 8;
	else if (spec->type == 'x')
		base = 16;
	else if (spec->type == 'X')
		base = 16;
	nb = va_arg(*ap, unsigned long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_uitoa_base((unsigned char)nb, base, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_uitoa_base((unsigned short int)nb, base, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_uitoa_base((unsigned long long)nb, base, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_uitoa_base((unsigned long long)nb, base, spec);
	else
		res = ft_uitoa_base((unsigned int)nb, base, spec);
	return (res);
}

char	*type_c(char *res, va_list *ap)
{
	int	ch;

	ch = va_arg(*ap, int);
	res = (char*)malloc(2 * sizeof(char));
	if (!ch)
		g_zero = 1;
	res[0] = ch;
	res[0] = (char)res[0];
	res[1] = '\0';
	return (res);
}
