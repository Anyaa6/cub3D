/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 08:14:45 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/03 17:45:35 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (len > s_len)
		len = s_len;
	if ((!(new = (char *)malloc(len + 1))))
		return (0);
	i = -1;
	while (++i < len)
		new[i] = s[start + i];
	new[i] = '\0';
	return (new);
}
