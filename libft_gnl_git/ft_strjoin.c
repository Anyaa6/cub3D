/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:45:28 by abonnel           #+#    #+#             */
/*   Updated: 2020/11/30 13:45:04 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int			s1_len;
	int			s2_len;
	char		*r;
	int			i;
	int			j;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(r = (char *)malloc((s1_len + s2_len + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (++i < s1_len)
		r[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		r[i + j] = s2[j];
	r[i + j] = '\0';
	return (r);
}
