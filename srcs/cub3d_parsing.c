/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:29:18 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/02 17:04:38 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_resolution(t_cub3d *cub, char *line, t_p *p)
{
	int				sizex;
	int				sizey;

	if (*(++line) != ' ')
		error(5, p);
	mlx_get_screen_size(cub->mlx_p, &sizex, &sizey);
	if ((check_res_input(++line, sizex, p) == 1) || ft_atoi(line) > sizex)
		cub->r_wid = sizex;
	else
		cub->r_wid = ft_atoi(line);
	//printf("line apres x = %s\n", line);
	while (*line != ' ')
		line++;
	//printf("line apres x = %s\n", line);
	if ((check_res_input(line, sizey, p) == 1) || ft_atoi(line) > sizey)
		cub->r_hgt = sizey;
	else
		cub->r_hgt = ft_atoi(line);
	//dprintf(1,"R width = %d, R height = %d and sizex = %d, sizey = %d\n", cub->r_wid, cub ->r_hgt, sizex, sizey);
}

void		floor_ceiling_color(t_cub3d *cub, char *line, int i, t_p *p)
{
	int				r;
	int				g;
	int				b;
		
	if (check_floor_ceiling_clr_input(line) == 1)
		error(8, p);
	r = ft_atoi(line + i);
	while (line[i] != ',' && line[i])
		i++;
	g = ft_atoi(line + (++i));
	while (line[i] != ',' && line[i])
		i++;
	b = ft_atoi(line + i + 1);
	if (line[0] == 'F')
		cub->floor = (r * 65536) + (g * 256) + b;
	else
		cub->top = (r * 65536) + (g * 256) + b;
	//dprintf(1,"cub->floor = %d, cub top = %d\n", cub->floor, cub->top);
}

void		elements_path(t_cub3d *cub, char *line, int i)
{
	if (line[i] == 'S' && line[i + 1] != 'O')
		cub->sp = ft_strdup((line + 1 + skip_space(line + 1)));
	else if (line[i] == 'N')
		cub->no = ft_strdup((line + 2 + skip_space(line + 2)));
	else if (line[i] == 'S')
		cub->so =  ft_strdup((line + 2 + skip_space(line + 2)));
	else if (line[i] == 'E')
		cub->ea =  ft_strdup((line + 2 + skip_space(line + 2)));
	else if (line[i] == 'W')
		cub->we =  ft_strdup((line + 2 + skip_space(line + 2)));
//	printf("s = %s\n no = %s\n so = %s\n ea = %s\n we = %s\n", cub->sprite, cub->no, cub->so, cub->ea, cub->we);	
//	erreur?
}

void		graphic_specs(t_cub3d *cub, char *line, t_p *p)
{
	int				i;

	i = 0;
	//dprintf(1,"ICI, line = %s\n", line);
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
			break;
		element_count++;
		free(*line);
	}
	if (gnl_return == -1)
        error(1, p);
	if (element_count != 8)
        error(6, p);
}
// a raccourcir, eventuellement envoyer element_count comme petre de parsing_cub pour gagner deux lignes
void     	parsing_cub(char *argv1, t_p *p)
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

