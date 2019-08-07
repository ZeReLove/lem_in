/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:11:20 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:34:07 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_and_smth(const char *format, va_list *ap)
{
	char		*copy;
	size_t		len;

	len = ft_strlen(format);
	copy = ft_strnew(len);
	ft_strcpy(copy, format);
	g_i = 0;
	while (format[g_i])
	{
		if (format[g_i] == '%')
			process_specifier(copy, ap);
		else
		{
			write(1, &format[g_i], 1);
			g_i++;
			g_ret++;
		}
	}
	free((char*)copy);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;

	g_ret = 0;
	g_zero = 0;
	va_start(ap, format);
	print_and_smth(format, &ap);
	va_end(ap);
	return (g_ret);
}
