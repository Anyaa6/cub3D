/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:08 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/02 17:04:36 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			move_front_back(int keycode, t_cub3d *cub)
{
	if (keycode == 13 || keycode == 126)//forward W
	{
		if (cub->dir > 90.0 && cub->dir < 270.0)
			cub->x0 -= 0.4 * fabs(cos(rad(cub->dir)));
		else if (cub->dir < 90.0 || cub->dir > 270.0)
			cub->x0 += 0.4 * fabs(cos(rad(cub->dir)));
		if (cub->dir > 0.0 && cub->dir < 180.0)
			cub->y0 -= 0.4 * fabs(sin(rad(cub->dir)));
		else if (cub->dir > 180.0 && cub->dir < 360.0)
			cub->y0 += 0.4 * fabs(sin(rad(cub->dir)));
	}
	else if (keycode == 1 || keycode == 125)// back S
	{
		if (cub->dir > 90.0 && cub->dir < 270.0)
			cub->x0 += 0.4 * fabs(cos(rad(cub->dir)));
		else if (cub->dir < 90.0 || cub->dir > 270.0)
			cub->x0 -= 0.4 * fabs(cos(rad(cub->dir)));
		if (cub->dir > 0.0 && cub->dir < 180.0)
			cub->y0 += 0.4 * fabs(sin(rad(cub->dir)));
		else if (cub->dir > 180.0 && cub->dir < 360.0)
			cub->y0 -= 0.4 * fabs(sin(rad(cub->dir)));
	}
}

void			move_left(t_cub3d *cub)
{
	double			dir_bis;

	if ((dir_bis = cub->dir + 90.0) >= 360.0)
		dir_bis -= 360.0;
	if (dir_bis >= 90.0 && dir_bis <= 270.0)
		cub->x0 -= 0.4 * fabs(cos(rad(dir_bis)));
	else if (dir_bis < 90.0 || dir_bis > 270.0)
		cub->x0 += 0.4 * fabs(cos(rad(dir_bis)));
	if (dir_bis >= 0.0 && dir_bis <= 180.0)
		cub->y0 -= 0.4 * fabs(sin(rad(dir_bis)));
	else if (dir_bis > 180.0 && dir_bis <= 360.0)
		cub->y0 += 0.4 * fabs(sin(rad(dir_bis)));
}

void			move_right(t_cub3d *cub)
{
	double			dir_bis;

	if ((dir_bis = cub->dir - 90.0) <= 0.0)
		dir_bis += 360.0;//right
	if (dir_bis >= 90.0 && dir_bis <= 270.0)
		cub->x0 -= 0.4 * fabs(cos(rad(dir_bis)));
	else if (dir_bis < 90.0 || dir_bis > 270.0)
		cub->x0 += 0.4 * fabs(cos(rad(dir_bis)));
	if (dir_bis >= 0.0 && dir_bis <= 180.0)
		cub->y0 -= 0.4 * fabs(sin(rad(dir_bis)));
	else if (dir_bis > 180.0 && dir_bis <= 360.0)
		cub->y0 += 0.4 * fabs(sin(rad(dir_bis)));
}

void			rotation(int keycode, t_cub3d *cub)
{
	if (keycode == 123)//left
	{
		if ((cub->dir += 3.0) >= 360.0)
			cub->dir -= 360.0;
	}
	else if (keycode == 124)//right
	{
		if ((cub->dir -= 3.0) < 0.0)
			cub->dir += 360.0;
	}
}
