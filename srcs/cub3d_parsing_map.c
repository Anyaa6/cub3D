/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:04:06 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 13:14:15 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_map_char(char *map, t_p *p)
{
	int				i;
	int				start;

	start = 0;
	i = 0;
	while (map[i])
	{
		if (map[i] == ' ' || map[i] == '0' || map[i] == '1' || map[i] == '2' \
				|| map[i] == '\n')
			i++;
		else if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' \
				|| map[i] == 'E')
		{
			if (start++ == 0)
				i++;
			else
				error(9, p);
		}
		else
			error(10, p);
	}
	if (start == 0)
		error(9, p);
}

void		map_wid_hgt(char *map, t_cub3d *cub)
{
	int				i;
	int				line_len;
	int				line_nb;

	i = 0;
	line_len = 0;
	line_nb = 0;
	while (map[i])
	{
		while (map[i] != '\n' && map[i])
		{
			line_len++;
			i++;
		}
		if (map[i] == '\n' && map[i])
		{
			line_nb++;
			i++;
		}
		if (cub->map_w < line_len)
			cub->map_w = line_len;
		line_len = 0;
	}
	cub->map_h = line_nb;
}

void		create_map(char *map, t_cub3d *cub, t_p *p)
{
	int				y;
	int				x;
	int				i;

	if (!(cub->map = (char **)malloc(sizeof(char *) * (cub->map_h + 1))))
		error(14, p);
	cub->map[cub->map_h] = NULL;
	y = 0;
	i = 0;
	while (y < cub->map_h)
	{
		if (!(cub->map[y] = (char *)malloc(sizeof(char) * cub->map_w + 1)))
			error(14, p);
		x = 0;
		while (map[i + x] != '\n' && map[i + x])
		{
			cub->map[y][x] = map[i + x];
			x++;
		}
		i += x + 1;
		while (x <= cub->map_w)
			cub->map[y][x++] = '\0';
		y++;
	}
}

void		clean_map_wid_hgt(t_cub3d *cub)
{
	int				y;
	int				x;
	int				line_len;
	int				line_nb;

	y = 0;
	x = 0;
	line_len = 0;
	cub->map_w = 0;
	line_nb = 0;
	while (cub->map[y] != NULL)
	{
		line_len = ft_strlen(cub->map[y]) - 1;
		while (line_len >= 0 && cub->map[y][line_len] == ' ')
			cub->map[y][line_len--] = '\0';
		line_len = ft_strlen(cub->map[y]);
		if (line_len > cub->map_w)
			cub->map_w = line_len;
		y++;
	}
	while (cub->map[y - 1][0] == '\0')
		y--;
	cub->map_h = y;
}

void		get_map(int fd, t_p *p, char *line)
{
	char			*map;
	int				gnl_return;

	map = strjoin_free1(line, "\n");
	while ((gnl_return = get_next_line(fd, &line)) > 0)
	{
		map = strjoin_free1(map, line);
		map = strjoin_free1(map, "\n");
		free_set_null(&line);
	}
	check_map_char(map, p);
	map_wid_hgt(map, p->cub);
	create_map(map, p->cub, p);
	map_is_closed(p->cub, p);
	clean_map_wid_hgt(p->cub);
	free_set_null(&map);
	free_set_null(&line);
}
