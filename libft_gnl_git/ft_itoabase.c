/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 11:48:27 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/24 11:48:55 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoabase(unsigned long long nb, char *base)
{
	int						nb_len;
	char					*nb_string;

	nb_len = 0;
	nb_len = hexa_len(nb);
	if (!(nb_string = (char *)ft_calloc(sizeof(char), (nb_len + 1))))
		return (0);
	nb_string[nb_len--] = '\0';
	while (nb >= 16)
	{
		nb_string[nb_len] = base[nb % 16];
		nb_len--;
		nb /= 16;
		if (nb_len < 0)
			break ;
	}
	nb_string[nb_len] = base[nb % 16];
	return (nb_string);
}
