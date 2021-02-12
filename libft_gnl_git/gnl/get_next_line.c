/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:59:12 by abonnel           #+#    #+#             */
/*   Updated: 2021/01/15 14:50:52 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				n_in(char *str)
{
	int				i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	if (str[i] == '\0')
		return (-1);
	return (-2);
}

void			free_set_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/*
** GNL return value
** 1 : a line was read
** 0 : EOF
** -1 : an error occured
*/

int				get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				n_pos;
	int				nb_bytes;
	static char		*s[4096];

	if (!line || BUFFER_SIZE < 1 || fd < 0)
		return (-1);
	if (!s[fd])
		s[fd] = ft_calloc(2, sizeof(char));
	while ((n_pos = n_in(s[fd])) == -1)
	{
		nb_bytes = read(fd, buf, BUFFER_SIZE);
		if (nb_bytes <= 0)
		{
			if (nb_bytes == 0)
				*line = ft_strdup(s[fd]);
			free_set_null(&(s[fd]));
			return (nb_bytes);
		}
		buf[nb_bytes] = '\0';
		s[fd] = strjoin_free1(s[fd], buf);
	}
	*line = substr_gnl(s[fd], 0, n_pos);
	s[fd] = substr_gnl(s[fd], n_pos + 1, ft_strlen(s[fd]) - (n_pos + 1));
	return (1);
}
