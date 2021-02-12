/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:48:12 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/02 08:09:40 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		s_len;
	char	*s_bis;
	int		i;

	s_len = ft_strlen(s1);
	if (!(s_bis = (char *)malloc(sizeof(char) * (s_len + 1))))
		return (0);
	i = -1;
	while (s1[++i])
		s_bis[i] = s1[i];
	s_bis[i] = '\0';
	return (s_bis);
}
