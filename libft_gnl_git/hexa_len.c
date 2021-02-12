/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:30:11 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/24 11:49:17 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				hexa_len(unsigned long long nb)
{
	int						nb_len;

	nb_len = 1;
	while (nb >= 16)
	{
		nb_len++;
		nb /= 16;
	}
	return (nb_len);
}
