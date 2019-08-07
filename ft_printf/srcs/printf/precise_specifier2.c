/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_specifier2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:13:09 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:41:11 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*s_precise(char *res, t_spec *spec)
{
	char	*ret;

	if ((int)ft_strlen((char*)res) > spec->precision)
	{
		if (!(ret = ft_strnew((int)spec->precision)))
			return (NULL);
		ft_strncpy(ret, (char*)res, (int)spec->precision);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*f_precise(char *res, t_spec *spec)
{
	int		i;
	char	*ret;
	int		count;

	i = 0;
	count = 0;
	while (res[i] != '.')
		i++;
	if ((int)ft_strlen((char*)(&res[++i])) < spec->precision)
	{
		if (!(ret = ft_strnew((int)spec->precision)))
			return (NULL);
		while (res[i])
		{
			i++;
			count++;
		}
		ft_strncpy(ret, (char*)res, (int)spec->precision);
		ft_memset((char*)(&ret[i]), '0', (int)(spec->precision - count));
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*first_zero(char *res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '0')
			return (&res[i]);
		i++;
	}
	return (NULL);
}
