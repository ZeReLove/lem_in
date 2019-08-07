/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:58:09 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:31:06 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero_flag(char *res, t_spec *spec)
{
	int		len;
	int		i;

	i = 0;
	if (g_zero)
		spec->width -= 1;
	len = (int)ft_strlen((char*)res);
	while (spec->flags[i])
	{
		if (spec->flags[i] == '-')
			return (res);
		i++;
	}
	if (((spec->type == 'i' || spec->type == 'd' || spec->type == 'u'
		|| spec->type == 'o' || spec->type == 'X' || spec->type == 'x')
		&& spec->precision == -1) || spec->type == 'f' || spec->type == 'p' ||
		spec->type == 's' || spec->type == 'c' || spec->type == '%')
	{
		if (len < spec->width)
			return (zero_flag2(&res, spec, len));
	}
	return (res);
}

char	*zero_flag2(char **res, t_spec *spec, int len)
{
	char	*ret;
	int		size;

	size = spec->width;
	if (!(ret = ft_strnew((int)size)))
		return (NULL);
	ft_memset(ret, '0', spec->width - len);
	ft_strcpy(&ret[(spec->width) - len], (char*)res[0]);
	free((char*)res[0]);
	return (ret);
}

char	*plus_flag(char *res, t_spec *spec)
{
	int		len;
	char	*point;

	point = NULL;
	len = (int)ft_strlen((char*)res);
	if (spec->type == 'i' || spec->type == 'd')
	{
		if (!check_minus(res, &point))
		{
			if (spec->precision == -1 && res[0] == '0' && res[1] != ' ' &&
			res[1] != '\0')
			{
				res[0] = '+';
				return (res);
			}
			if (res[len - 1] == ' ')
				return (plus_flag2(res, &len));
			else
				return (plus_flag3(res, &len));
		}
	}
	return (res);
}

char	*plus_flag2(char *res, int *len)
{
	char	*ret;

	if (!(ret = ft_strnew((int)len[0])))
		return (NULL);
	ft_strncpy(&ret[1], res, (int)len[0] - 1);
	ret[0] = '+';
	free((char*)res);
	return (ret);
}

char	*plus_flag3(char *res, int *len)
{
	char	*ret;

	if (!(ret = ft_strnew((int)len[0] + 1)))
		return (NULL);
	ret[0] = '+';
	ft_strcpy(&ret[1], (char*)res);
	free((char*)res);
	return (ret);
}
