/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_specifier2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:58:34 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 17:07:03 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_specifier(char *res, t_spec *spec, int flag)
{
	if (spec->flags[flag] == '0')
		res = zero_flag(res, spec);
	else if (spec->flags[flag] == '-')
		res = minus_flag(res, spec);
	else if (spec->flags[flag] == '+')
		res = plus_flag(res, spec);
	else if (spec->flags[flag] == '#')
		res = hash_flag(res, spec);
	else if (spec->flags[flag] == ' ')
		res = space_flag(res, spec);
	return (res);
}

char	*hash_flag(char *res, t_spec *spec)
{
	int		len;
	char	*ret;

	ret = NULL;
	len = (int)ft_strlen((char*)res);
	if (spec->type == 'o')
	{
		if (res[len - 1] == ' ')
		{
			if (!(ret = ft_strnew(len)))
				return (NULL);
			ft_strncpy(&ret[1], res, len - 1);
			ret[0] = '0';
			free((char*)res);
			return (ret);
		}
		else
			return (hash_flag_else(res, spec, len));
	}
	if (spec->type == 'x' || spec->type == 'X')
		return (hash_flag_forx_bigx(res, spec, &len));
	return (res);
}

char	*minus_flag(char *res, t_spec *spec)
{
	int		len;
	char	*ret;
	int		size;

	len = (int)ft_strlen((char*)res);
	size = spec->width;
	if (spec->precision > spec->width)
		return (res);
	if (len < spec->width)
	{
		if (!(ret = ft_strnew((int)size)))
			return (NULL);
		ft_strcpy(&ret[0], (char*)res);
		ft_memset((void*)(&ret[len]), ' ', spec->width - len);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*hash_flag_forx_bigx(char *res, t_spec *spec, int *len)
{
	char	*ret;

	if (res[0] == '0')
		return (res);
	if (!(ret = ft_strnew((int)len[0] + 2)))
		return (NULL);
	ret[0] = '0';
	if (spec->type == 'x')
		ret[1] = 'x';
	if (spec->type == 'X')
		ret[1] = 'X';
	ft_strcpy(&ret[2], (char*)res);
	free((char*)res);
	return (ret);
}

char	*hash_flag_else(char *res, t_spec *spec, int len)
{
	char	*ret;

	if (res[0] == '0' && res[1] == '\0' && spec->precision == -1)
		return (res);
	if (!(ret = ft_strnew(len + 1)))
		return (NULL);
	ret[0] = '0';
	ft_strcpy(&ret[1], (char*)res);
	free((char*)res);
	return (ret);
}
