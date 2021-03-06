/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_ray_wall_hgt.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:09:15 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 14:13:08 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			first_h_intersection(t_cubray *ray)
{
	double			xstep;
	double			ystep;

	if (ray->y_dir < 0)
		ray->yh = floor(ray->y0);
	else
		ray->yh = ceil(ray->y0);
	ystep = fabs(ray->y0 - ray->yh);
	xstep = fabs(ystep / tan(ray->fov));
	if (ray->x_dir < 0)
		ray->xh = ray->x0 - xstep;
	else
		ray->xh = ray->x0 + xstep;
}

void			first_v_intersection(t_cubray *ray)
{
	double			xstep;
	double			ystep;

	if (ray->x_dir < 0)
		ray->xv = floor(ray->x0);
	else
		ray->xv = ceil(ray->x0);
	xstep = fabs(ray->x0 - ray->xv);
	ystep = fabs(xstep * tan(ray->fov));
	if (ray->y_dir < 0)
		ray->yv = ray->y0 - ystep;
	else
		ray->yv = ray->y0 + ystep;
}

int				check_h_wall(t_cub3d *cub, t_cubray *ray, t_p *p)
{
	if (ray->y_dir < 0)
	{
		if ((int)floor(ray->yh - 1.0) < 0 || (int)floor(ray->xh) < 0 \
				|| (int)floor(ray->yh - 1.0) > (cub->map_h - 1) \
				|| (int)floor(ray->xh) > (cub->map_w - 1))
			return (-1);
		else if (cub->map[(int)floor(ray->yh - 1.0)][(int)floor(ray->xh)] == \
				'o')
			return (1);
		else if (cub->map[(int)floor(ray->yh - 1.0)][(int)floor(ray->xh)] == \
				'X')
			add_sprite(&p->spr, p, ray->yh - 1.0, ray->xh);
	}
	else
	{
		if ((int)floor(ray->yh) < 0 || (int)floor(ray->xh) < 0 || \
				(int)floor(ray->yh) > cub->map_h - 1 || (int)floor(ray->xh) > \
				cub->map_w - 1)
			return (-1);
		else if (cub->map[(int)floor(ray->yh)][(int)floor(ray->xh)] == 'o')
			return (1);
		else if (cub->map[(int)floor(ray->yh)][(int)floor(ray->xh)] == 'X')
			add_sprite(&p->spr, p, ray->yh, ray->xh);
	}
	return (0);
}

int				check_v_wall(t_cub3d *cub, t_cubray *ray, t_p *p)
{
	if (ray->x_dir < 0)
	{
		if ((int)floor(ray->yv) < 0 || (int)floor(ray->xv - 1.0) < 0 \
				|| (int)floor(ray->yv) > cub->map_h - 1 \
				|| (int)floor(ray->xv - 1.0) > cub->map_w - 1)
			return (-1);
		else if (cub->map[(int)floor(ray->yv)][(int)floor(ray->xv - 1.0)] \
				== 'o')
			return (1);
		else if (cub->map[(int)floor(ray->yv)][(int)floor(ray->xv - 1.0)] \
				== 'X')
			add_sprite(&p->spr, p, ray->yv, ray->xv - 1.0);
	}
	else
	{
		if ((int)floor(ray->yv) < 0 || (int)floor(ray->xv) < 0\
				|| (int)floor(ray->yv) > cub->map_h - 1 \
				|| (int)floor(ray->xv) > cub->map_w - 1)
			return (-1);
		else if (cub->map[(int)floor(ray->yv)][(int)floor(ray->xv)] == 'o')
			return (1);
		else if (cub->map[(int)floor(ray->yv)][(int)floor(ray->xv)] == 'X')
			add_sprite(&p->spr, p, ray->yv, ray->xv);
	}
	return (0);
}
