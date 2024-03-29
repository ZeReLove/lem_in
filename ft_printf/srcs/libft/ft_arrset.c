/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:42:36 by bconwy            #+#    #+#             */
/*   Updated: 2019/08/07 20:03:45 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*ft_arrset(int *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		b[i] = c;
		i++;
	}
	return (b);
}
