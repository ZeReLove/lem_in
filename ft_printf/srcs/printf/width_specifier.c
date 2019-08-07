/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:58:24 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 17:15:48 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*width_specifier(char *res, t_spec *spec)
{
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen((char*)res);
	if (g_zero)
		spec->width -= 1;
	while (spec->flags[i])
	{
		if (width_specifier2(&res, spec, &i))
			return (res);
	}
	i = 0;
	if (len < spec->width)
		return (width_specifier3(&res, spec, &i, len));
	return (res);
}

int		width_specifier2(char **res, t_spec *spec, int *i)
{
	int		flag;

	flag = 0;
	if (spec->flags[*i] == '-')
	{
		res[0] = minus_flag(res[0], spec);
		flag = 1;
	}
	if (spec->flags[*i] == '0' && (spec->type == 'o' || spec->type == 's'))
	{
		res[0] = zero_flag(res[0], spec);
		flag = 1;
	}
	(*i)++;
	return (flag);
}

char	*width_specifier3(char **res, t_spec *spec, int *i, int len)
{
	int		size;
	char	*ret;

	size = spec->width;
	if (!(ret = ft_strnew((int)size)))
		return (NULL);
	while (*i < spec->width - len)
		ret[(*i)++] = ' ';
	ft_strcpy(&ret[*i], (char*)res[0]);
	free((char*)res[0]);
	return (ret);
}

char	*space_flag(char *res, t_spec *spec)
{
	int		len;
	int		i;
	char	*point;

	i = 0;
	point = NULL;
	while (spec->flags[i])
	{
		if (spec->flags[i] == '+' && !check_zero(res))
			return (res);
		i++;
	}
	len = (int)ft_strlen((char*)res);
	if (spec->type == 'd' || spec->type == 'f' || spec->type == 'i')
	{
		if (!check_minus(res, &point))
			return (space_flag2(&res, spec, len));
	}
	return (res);
}

char	*space_flag2(char **res, t_spec *spec, int len)
{
	char	*ret;

	if (check_zero(res[0]) && res[0][len - 1] == ' ')
	{
		if (!(ret = ft_strnew(len + 1)))
			return (NULL);
		ft_strncpy(&ret[1], res[0], (int)(len - 1));
		ret[0] = ' ';
		return (ret);
	}
	if (res[0][0] == '0' && res[0][1] != '\0' && spec->precision == -1)
	{
		res[0][0] = ' ';
		return (res[0]);
	}
	if (!(ret = ft_strnew(len + 1)))
		return (NULL);
	ret[0] = ' ';
	ft_strcpy(&ret[1], res[0]);
	free(res[0]);
	return (ret);
}
