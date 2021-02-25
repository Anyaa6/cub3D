/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_raycasting_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:27:16 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 13:28:07 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_x_y_direction(t_cubray *ray)
{
	if (ray->fov >= rad(0.1) && ray->fov <= rad(90.0))
	{
		ray->x_dir = 1;
		ray->y_dir = -1;
	}
	else if (ray->fov >= rad(90.1) && ray->fov <= rad(180.0))
	{
		ray->x_dir = -1;
		ray->y_dir = -1;
	}
	else if (ray->fov >= rad(180.1) && ray->fov <= rad(270.0))
	{
		ray->x_dir = -1;
		ray->y_dir = 1;
	}
	else if (ray->fov >= rad(270.1) && ray->fov <= rad(360.0))
	{
		ray->x_dir = 1;
		ray->y_dir = 1;
	}
}

void			init_ray_struct(t_cub3d *cub, t_cubray *ray)
{
	ray->x0 = cub->x0;
	ray->y0 = cub->y0;
	ray->eye_h = (float)cub->r_hgt / 2.0;
	ray->s_dist = ((float)cub->r_wid / 2.0) / tan(rad(30.0));
	if ((ray->fov = rad(cub->dir + 30.0)) >= rad(360.0))
		ray->fov -= rad(360.0);
	set_x_y_direction(ray);
}

void			set_start_stop(int *stop, double *ytxt, double *step, t_p *p)
{
	*step = (float)(p->img->imgs_h) / p->ray->w_hgt;
	if (p->ray->w_hgt < p->cub->r_hgt)
	{
		*ytxt = 0.0;
		p->img->y = abs((p->cub->r_hgt - (int)floor(p->ray->w_hgt))) / 2;
		*stop = p->cub->r_hgt - p->img->y;
	}
	else
	{
		*ytxt = ((p->ray->w_hgt - (float)(p->cub->r_hgt)) / 2) * *step;
		p->img->y = 0;
		*stop = p->cub->r_hgt;
	}
}

void			set_xtxt(t_cubray *ray)
{
	ray->xtxt = 0;
	if (ray->x == ray->xv && ray->y == ray->yv)
		ray->xtxt = 256 * modf(ray->y, &(ray->trash));
	else if (ray->x == ray->xh && ray->y == ray->yh)
		ray->xtxt = 256 * modf(ray->x, &(ray->trash));
}
