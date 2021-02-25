/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:31:45 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 13:31:59 by abonnel          ###   ########lyon.fr   */
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
	while (*line != ' ')
		line++;
	if ((check_res_input(line, sizey, p) == 1) || ft_atoi(line) > sizey)
		cub->r_hgt = sizey;
	else
		cub->r_hgt = ft_atoi(line);
}
