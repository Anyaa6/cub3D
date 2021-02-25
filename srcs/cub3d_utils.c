/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:42:26 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 13:09:42 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			skip_space(char *s)
{
	int				i;

	i = 0;
	while (s[i] == ' ' && s[i])
		i++;
	return (i);
}

void		clean_map(t_cub3d *cub)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1' || cub->map[y][x] == '0' \
					|| cub->map[y][x] == '2')
				cub->map[y][x] = ' ';
			x++;
		}
		y++;
		x = 0;
	}
}

void		display_map(t_cub3d *cub)
{
	int		y;

	y = 0;
	while (cub->map[y])
	{
		printf("%s\n", cub->map[y]);
		y++;
	}
	printf("\n");
}

double		rad(double degrees)
{
	double			radians;

	return (radians = degrees * (M_PI / 180.0));
}

double		deg(double radians)
{
	double			degrees;

	return (degrees = radians * (180.0 / M_PI));
}
