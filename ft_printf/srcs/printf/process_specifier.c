/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:06:33 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/30 15:43:22 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		process_specifier(char *format, va_list *ap)
{
	t_process process;

	process.dot = 0;
	process.flag = -1;
	process.k = 0;
	find_width_param(&format[g_i], ap, &process.spec);
	g_i++;
	while (format[g_i] && format[g_i] != 'c' && format[g_i] != 's' &&
			format[g_i] != 'p' && format[g_i] != 'd' && format[g_i] != 'i' &&
			format[g_i] != 'o' && format[g_i] != 'u' && format[g_i] != 'x' &&
			format[g_i] != 'X' && format[g_i] != 'f' && format[g_i] != '%')
	{
		if (format[g_i] == '.')
			process.dot = 1;
		g_i++;
	}
	if (format[g_i] == '\0')
	{
		one_percent_only(format);
		return ;
	}
	process_specifier5(format, ap, &process.spec, &process);
}

void		process_specifier5(char *format, va_list *ap, t_spec *spec,
			t_process *process)
{
	spec->type = format[g_i];
	process->j = g_i;
	g_i++;
	format[process->j--] = '\0';
	if (format[process->j] == 'h' || format[process->j] == 'l' ||
		format[process->j] == 'L')
		process_specifier2(format, &process->spec, &process->j);
	else
		spec->size[0] = '\0';
	if (process->dot)
		process_specifier3(format, &process->spec, &process->j, ap);
	else
		spec->precision = -1;
	while (format[process->j] != '%')
		process->j--;
	process->j++;
	while (format[process->j] == '0' || format[process->j] == '#' ||
			format[process->j] == '+' || format[process->j] == '-' ||
			format[process->j] == ' ')
		process_specifier4(format, &process->spec, &process->flag, &process->j);
	if (format[process->j] <= '9' && format[process->j] >= '1')
		spec->width = ft_atoi((char*)(&format[process->j]));
	else
		spec->width = -1;
	call_specifier(ap, &process->spec, process->flag);
}

void		process_specifier4(char *format, t_spec *spec, int *flag, int *j)
{
	int k;

	k = 0;
	while (k < 5)
	{
		if (spec->flags[k] == format[j[0]])
			break ;
		k++;
	}
	if (k == 5)
	{
		flag[0]++;
		spec->flags[flag[0]] = format[j[0]];
	}
	j[0]++;
	k = 0;
}

void		process_specifier3(char *format, t_spec *spec, int *j, va_list *ap)
{
	while (format[j[0]] != '.')
		j[0]--;
	if (format[j[0] + 1] == '*')
		spec->precision = va_arg(*ap, int);
	if (format[j[0] + 1] == '\0')
		spec->precision = 0;
	else
		spec->precision = ft_atoi((char*)(&format[j[0] + 1]));
	format[j[0]] = '\0';
}

void		process_specifier2(char *format, t_spec *spec, int *j)
{
	if (format[j[0] - 1] == 'l' || format[j[0] - 1] == 'h')
	{
		spec->size[1] = format[j[0]];
		j[0]--;
	}
	else
		spec->size[1] = '\0';
	spec->size[0] = format[j[0]];
	format[j[0]] = '\0';
}
