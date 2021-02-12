/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:46:26 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/02 15:42:35 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		flood_fill_map(int x, int y, t_cub3d *cub, t_p *p)
{
	if (x < 0 || y < 0 || cub->map[y] == NULL \
			|| cub->map[y][x] == '\0' \
			|| cub->map[y][x] == ' ')
		error(11, p);
	else if (cub->map[y][x] == '1')
	{
		cub->map[y][x] = 'o';
		return ;
	}
	else if (cub->map[y][x] == '0' || cub->map[y][x] == '2')
	{
		if (cub->map[y][x] == '0')
			cub->map[y][x] = '.';
		else if (cub->map[y][x] == '2')
			cub->map[y][x] = 'X';
		flood_fill_map(x + 1, y, cub, p);//right 
		flood_fill_map(x - 1, y, cub, p);//left
		flood_fill_map(x, y - 1, cub, p);//up
		flood_fill_map(x, y + 1, cub, p);//down
		flood_fill_map(x + 1, y + 1, cub, p);
		flood_fill_map(x - 1, y + 1, cub, p);
		flood_fill_map(x + 1, y - 1, cub, p);
		flood_fill_map(x - 1, y - 1, cub, p);
	}
}

void		dir_angle(t_cub3d *cub)
{
	if (cub->dir_start == 'N')
        cub->dir = 90.0;
    else if (cub->dir_start == 'W')
        cub->dir = 180.0;
    else if (cub->dir_start == 'S')
        cub->dir = 270.0;
    else if (cub->dir_start == 'E')
        cub->dir = 0.0;
}

void		digit_around(t_cub3d *cub, int x, int y, t_p *p)
{
	if (ft_isdigit(cub->map[y][x]) == 0 \
			|| ft_isdigit(cub->map[y][x + 1]) == 0 \
			|| ft_isdigit(cub->map[y][x + 2]) == 0 \
			|| ft_isdigit(cub->map[y + 1][x]) == 0 \
			|| ft_isdigit(cub->map[y + 2][x]) == 0 \
			|| ft_isdigit(cub->map[y + 1][x + 2]) == 0 \
			|| ft_isdigit(cub->map[y + 2][x + 2]) == 0 \
			|| ft_isdigit(cub->map[y + 2][x + 1]) == 0 )
		error(11, p);
}

void		find_player_start(t_cub3d *cub, t_p *p)
{
	int				x;
	int				y;

	x = 0;
	y = 0;
	while (cub->map[y])
	{
		while (ft_isalpha(cub->map[y][x]) == 0 && cub->map[y][x])
			x++;
		if (ft_isalpha(cub->map[y][x]) == 1)
		{
			if (y == 0 || x == 0 || cub->map[y + 1] == NULL)
				error(11, p);
			digit_around(cub, x - 1, y - 1, p);
			cub->xstart = x;
			cub->ystart = y;
			cub->x0 = (float)cub->xstart + 0.5;
			cub->y0 = (float)cub->ystart + 0.5;
			cub->dir_start = cub->map[y][x];
			dir_angle(cub);
			//printf("player x = %d, y = %d, dir = %c\n\n", x, y, cub->dir_start);
			return ;
		}
		y++;
		x = 0;
	}
}

void        map_is_closed(t_cub3d *cub, t_p *p)
{
	int			x;
	int			y;

	find_player_start(cub, p);
	x = cub->xstart;
	y = cub->ystart;
	cub->map[y][x] = '0'; //changer point de depart comme si c'etait un 0	
	flood_fill_map(x, y, cub, p);
	cub->map[cub->ystart][cub->xstart] = cub->dir_start;
	clean_map(cub);
}
