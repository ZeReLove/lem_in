/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:11:33 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:39:03 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precise_specifier(char *res, t_spec *spec)
{
	char	*ret;

	if (spec->type == 'f')
		ret = f_precise(res, spec);
	else if (spec->type == 's')
		ret = s_precise(res, spec);
	else if (spec->type == 'p')
		ret = p_precise(res, spec);
	else if (spec->type == 'x' || spec->type == 'X')
		ret = x_bigx_precise(res, spec);
	else if (spec->type != 'c')
		ret = other_precise(res, spec);
	else
		ret = res;
	return (ret);
}

char	*x_bigx_precise(char *res, t_spec *spec)
{
	char	*ret;

	if (res[0] == '0' && (res[1] == 'x' || res[1] == 'X'))
		ret = p_precise(res, spec);
	else
		ret = other_precise(res, spec);
	return (ret);
}

char	*p_precise(char *res, t_spec *spec)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen((char*)res) - 2;
	if (spec->precision == 0 && res[2] == '0' && res[3] == '\0')
	{
		res[2] = '\0';
		return (res);
	}
	if (len < spec->precision)
	{
		if (!(ret = ft_strnew((int)spec->precision + 2)))
			return (NULL);
		while (i < spec->precision - len)
			ret[i++] = '0';
		ft_strcpy(&ret[i], (char*)res);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*other_precise(char *res, t_spec *spec)
{
	t_precise	params;

	params.point = NULL;
	params.precision = spec->precision;
	params.len = (int)ft_strlen((char*)res);
	if (g_zero)
		return (res);
	if (spec->precision == 0 && res[0] == '0' && res[1] == '\0')
	{
		res[0] = '\0';
		return (res);
	}
	if (res[0] == '0' && res[1] == '\0' && spec->type == 'o')
		return (res);
	if (check_minus(res, &(params.point)) && spec->precision > params.len - 1)
		params.precision += 1;
	if (params.precision == 0 && res[1] == '0' && res[2] == '\0')
	{
		res[1] = '\0';
		return (res);
	}
	if (params.len < params.precision && spec->type != '%')
		return (other_precise2(res, &params));
	return (res);
}

char	*other_precise2(char *res, t_precise *params)
{
	char *ret;

	params->i = 0;
	if (!(ret = ft_strnew((int)params->precision)))
		return (NULL);
	while (params->i < params->precision - params->len)
		ret[(params->i)++] = '0';
	ft_strcpy(&ret[params->i], (char*)res);
	free((char*)res);
	return (ret);
}
