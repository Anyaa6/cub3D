/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:31:45 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/26 12:17:07 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		res_digit_only(char *line, t_p *p)
{
	int				i;
	int				nb_count;

	i = 0;
	nb_count = 0;
	line++;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]))
		{
			nb_count++;
			while (ft_isdigit(line[i]))
				i++;
		}
	}
	if ((unsigned long)i != ft_strlen(line) || nb_count != 2)
		error(17, p);
}

void		get_resolution(t_cub3d *cub, char *line, t_p *p)
{
	int				sizex;
	int				sizey;

	res_digit_only(line, p);
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
	while (*line == ' ' || ft_isdigit(*line))
		line++;
	if (*line != '\0' || cub->r_hgt == 0 || cub->r_wid == 0)
		error(17, p);
}
