/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_specifier2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:07:52 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 17:10:00 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	one_percent_only(char *format)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = ft_strlen(format) - 1;
	while (format[j] != '%')
		j++;
	str = ft_strnew(i - j);
	j = i - j - 1;
	while (format[i] != '%')
	{
		str[j] = format[i];
		j--;
		i--;
	}
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		g_ret++;
	}
	free((char*)str);
}

void	ft_swapp(char *a, char *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	print_param(char *res)
{
	int		i;
	char	*point;

	i = 0;
	point = NULL;
	if (check_0x(res, &point) && res[0] == '0')
		ft_swapp(&res[1], point);
	while (res[i])
	{
		write(1, &res[i], 1);
		i++;
		g_ret++;
	}
	if (g_zero)
	{
		write(1, "\0", 1);
		g_ret++;
	}
	g_zero = 0;
}

void	clean_struct(t_spec *spec)
{
	spec->type = '\0';
	spec->precision = -1;
	spec->width = -1;
	spec->size[0] = '\0';
	spec->flags[0] = '\0';
}
