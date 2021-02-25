/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_sprites_math.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:37:58 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/24 17:35:17 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_start_stop_spr(t_p *p, t_cubspr *node)
{
	if (node->sp_hgt < p->cub->r_hgt)
	{
		node->yspr = 0.0;
		node->y0 = abs((p->cub->r_hgt - (int)floor(node->sp_hgt))) / 2;
	}
	else
	{
		node->yspr = ((node->sp_hgt - (float)(p->cub->r_hgt)) / 2) * node->step;
		node->y0 = 0;
	}
	node->yend = p->cub->r_hgt - node->y0;
}

void			mesures_to_sprcenter(t_p *p, t_cubspr *node)
{
	double				x;
	double				y;

	x = floor(node->xf) + 0.5;
	y = floor(node->yf) + 0.5;
	node->dx = x - p->ray->x0;
	node->dy = y - p->ray->y0;
	node->delta = fabs(acos(fabs(node->dx) / node->sp_dist));
	node->cdel = node->delta;
	if (node->dx < 0.0 && node->dy < 0.0)
		node->cdel = fabs(rad(180.0) - node->cdel);
	else if (node->dx <= 0.0 && node->dy > 0.0)
		node->cdel += rad(180.0);
	else if (node->dx >= 0.0 && node->dy >= 0.0)
		node->cdel = fabs(rad(360.0) - node->cdel);
}

void			xspr_step(t_p *p, t_cubspr *spr)
{
	double				fov;

	fov = p->ray->fov;
	if (deg(p->ray->fov) > 90.0 && deg(p->ray->fov) <= 270.0)
		fov = fabs(p->ray->fov - rad(180.0));
	else if (deg(p->ray->fov) > 270.0 && deg(p->ray->fov) <= 360)
		fov = fabs(p->ray->fov - rad(360.0));
	spr->beta = fabs(spr->cdel - p->ray->fov);
	spr->x_step = fabs(tan(spr->beta)) * spr->sp_dist;
	if (spr->cdel <= p->ray->fov)
	{
		if (fabs(spr->cdel - p->ray->fov) > rad(180.0))
			spr->xspr = 256.0 * (spr->x_step + 0.50);
		else
			spr->xspr = 256.0 * fabs(0.50 - spr->x_step);
	}
	else if (spr->cdel > p->ray->fov)
	{
		if (fabs(spr->cdel - p->ray->fov) > rad(180.0))
			spr->xspr = 256.0 * fabs(0.50 - spr->x_step);
		else
			spr->xspr = 256.0 * (spr->x_step + 0.50);
	}
}

double			dist_to_center(double yf, double xf, t_p *p)
{
	double				dist;

	xf = floor(xf) + 0.5;
	yf = floor(yf) + 0.5;
	dist = sqrt(pow(fabs(xf - p->ray->x0), 2.0) + \
			pow(fabs(yf - p->ray->y0), 2.0));
	return (dist);
}
