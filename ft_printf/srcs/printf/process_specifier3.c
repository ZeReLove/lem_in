/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_specifier3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:08:43 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:48:09 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	find_width_param(char *format, va_list *ap, t_spec *spec)
{
	int	j;

	j = 0;
	while (format[j] == '0' || format[j] == '#' || format[j] == '+'
			|| format[j] == '-')
		j++;
	if (format[j] == '*')
		spec->width = va_arg(*ap, int);
}

void	call_specifier(va_list *ap, t_spec *spec, int flag)
{
	char	*res;
	int		count;
	char	*point;

	count = -1;
	point = NULL;
	res = type_specifier(spec, ap);
	while (count < flag)
		call_specifier2(spec, &count, &res);
	if (spec->precision != -1)
		res = precise_specifier(res, spec);
	if (check_minus(res, &point) && res[0] != '-' && *(point - 1) == '0')
		ft_swapp(first_zero(res), point);
	if (check_plus(res, &point) && res[0] != '+' && *(point - 1) == '0')
		ft_swapp(first_zero(res), point);
	if (check_space(res, &point) && spec->type != 's')
		ft_swapp(&res[0], point);
	if (spec->width != -1)
		res = width_specifier(res, spec);
	print_param(res);
	clean_struct(spec);
	free((char*)res);
}

void	call_specifier2(t_spec *spec, int *count, char **res)
{
	count[0]++;
	if ((spec->flags[count[0]] == '-' || spec->flags[count[0]] == ' ' ||
		spec->flags[count[0]] == '+') && spec->type != 's')
		res[0] = precise_specifier(res[0], spec);
	res[0] = flag_specifier(res[0], spec, count[0]);
}
