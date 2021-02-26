/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:29:18 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/26 12:21:06 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		floor_ceiling_color(t_cub3d *cub, char *line, int i, t_p *p)
{
	int				r;
	int				g;
	int				b;

	if (ft_isdigit(line[1 + skip_space(line + 1)]) == 0)
	{
		sky_floor_texture(cub, line);
		return ;
	}
	if (check_floor_ceiling_clr_input(line) == 1)
		error(8, p);
	if ((r = ft_atoi(line + i)) > 255)
		r = 255;
	while (line[i] != ',' && line[i])
		i++;
	if ((g = ft_atoi(line + (++i))) > 255)
		g = 255;
	while (line[i] != ',' && line[i])
		i++;
	if ((b = ft_atoi(line + i + 1)) > 255)
		b = 255;
	if (line[0] == 'F')
		cub->floor = (r * 65536) + (g * 256) + b;
	else
		cub->top = (r * 65536) + (g * 256) + b;
}

void		elements_path(t_cub3d *cub, char *line, int i)
{
	if (line[i] == 'S' && line[i + 1] != 'O')
		cub->sp = ft_strdup((line + 1 + skip_space(line + 1)));
	else if (line[i] == 'N')
		cub->no = ft_strdup((line + 2 + skip_space(line + 2)));
	else if (line[i] == 'S')
		cub->so = ft_strdup((line + 2 + skip_space(line + 2)));
	else if (line[i] == 'E')
		cub->ea = ft_strdup((line + 2 + skip_space(line + 2)));
	else if (line[i] == 'W')
		cub->we = ft_strdup((line + 2 + skip_space(line + 2)));
}

void		graphic_specs(t_cub3d *cub, char *line, t_p *p)
{
	int				i;

	i = 0;
	if (line[0] == 'R')
		get_resolution(cub, line, p);
	else if (line[0] == 'F' || line[0] == 'C')
		floor_ceiling_color(cub, line, i + 1, p);
	else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || \
			line[0] == 'E')
		elements_path(cub, line, i);
	else
		error(2, p);
}

void		parsing_specs(t_p *p, char **line, int fd)
{
	int				gnl_return;
	int				element_count;

	element_count = 0;
	while ((gnl_return = get_next_line(fd, line)) > 0)
	{
		if (*line[0] == '\0')
		{
			free_set_null(line);
			continue;
		}
		if (ft_isalpha(*line[0]))
			graphic_specs(p->cub, *line, p);
		else
			break ;
		element_count++;
		free(*line);
	}
	if (gnl_return == -1)
		error(1, p);
	if (element_count != 8)
		error(6, p);
}

void		parsing_cub(char *argv1, t_p *p)
{
	int				fd;
	char			*line;

	if ((fd = open(argv1, O_RDONLY)) == -1)
		error(-1, p);
	line = NULL;
	parsing_specs(p, &line, fd);
	parsing_error(argv1, line, p);
	get_map(fd, p, line);
	if (close(fd) != 0)
		error(-1, p);
}
