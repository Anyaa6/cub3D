/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_raycasting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:20:45 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 13:56:31 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_wall_dist(t_cubray *ray, t_cubimg *img, double v_dist)
{
	if (ray->w_dist < 0)
		ray->w_dist = v_dist + 1.0;
	else if (v_dist < 0)
		v_dist = ray->w_dist + 1.0;
	if (v_dist > ray->w_dist)
	{
		ray->x = ray->xh;
		ray->y = ray->yh;
		if (ray->y_dir == 1)
			ray->txt = &(img->so_img);
		else if (ray->y_dir == -1)
			ray->txt = &(img->no_img);
	}
	else if (v_dist < ray->w_dist)
	{
		ray->x = ray->xv;
		ray->y = ray->yv;
		ray->w_dist = v_dist;
		if (ray->x_dir == 1)
			ray->txt = &(img->ea_img);
		else if (ray->x_dir == -1)
			ray->txt = &(img->we_img);
	}
}

void			find_wall_height(t_p *p, t_cubray *ray)
{
	double			xa;
	double			ya;
	double			v_dist;
	double			alpha;

	ray->w_dist = -1.0;
	first_h_intersection(ray);
	xa = fabs(1 / tan(ray->fov));
	while (check_h_wall(p->cub, ray, p) == 0)
		find_next_xy_h(ray, xa, 1.0);
	if (check_h_wall(p->cub, ray, p) == 1)
		ray->w_dist = fabs(fabs(ray->xh - ray->x0) / fabs(cos(ray->fov)));
	first_v_intersection(ray);
	ya = fabs(1 * tan(ray->fov));
	while (check_v_wall(p->cub, ray, p) == 0)
		find_next_xy_v(ray, 1.0, ya);
	v_dist = -1.0;
	if (check_v_wall(p->cub, ray, p) == 1)
		v_dist = fabs(fabs(ray->xv - ray->x0) / fabs(cos(ray->fov)));
	set_wall_dist(ray, p->img, v_dist);
	alpha = fabs(rad(p->cub->dir) - ray->fov);
	ray->w_dist = ray->w_dist * fabs(cos(alpha));
	ray->w_hgt = (ray->s_dist) / ray->w_dist;
}

void			draw_sprite(t_cubspr *spr, t_cubimg *img)
{
	int				y0;
	double			yspr;

	if (spr->x_step >= 0.5)
		return ;
	yspr = spr->yspr;
	y0 = spr->y0;
	while (spr->y0 < spr->yend)
	{
		if (img->sp_img[(int)round(spr->xspr) + (int)round(spr->yspr) * \
				img->txt_l] != img->sp_img[0])
			img->img[spr->i0 + (spr->y0 * img->lsize)] = \
				img->sp_img[(int)round(spr->xspr) + (int)round(spr->yspr) * \
				img->txt_l];
		spr->y0++;
		if ((spr->yspr += spr->step) > 245)
			break ;
	}
	spr->y0 = y0;
	spr->yspr = yspr;
}

void			draw(int x, t_p *p, t_cubimg *img, t_cubray *ray)
{
	int				stop;
	double			ytxt;
	double			step;

	set_xtxt(ray);
	set_start_stop(&stop, &ytxt, &step, p);
	if (p->first)
		del_if_further(p, ray, &(p->spr));
	while (img->y < stop)
	{
		if ((ray->xtxt + (((int)round(ytxt)) * img->txt_l)) >= img->imgs_h * \
				img->imgs_w)
			ytxt = 0.0;
		img->img[x + (img->y * img->lsize)] = (*ray->txt)[ray->xtxt + \
			(((int)round(ytxt)) * img->txt_l)];
		img->y++;
		ytxt += step;
	}
	while (p->spr)
	{
		if (p->spr->sp_dist < p->ray->w_dist)
			draw_sprite(p->spr, p->img);
		p->spr = p->spr->next;
	}
}

void			raycasting(t_cub3d *cub, t_cubimg *img, t_cubray *ray, t_p *p)
{
	init_ray_struct(cub, ray);
	ray->i = 0;
	while (ray->i < cub->r_wid)
	{
		find_wall_height(p, ray);
		draw(ray->i, p, img, ray);
		if ((ray->fov -= rad(60.0 / (float)cub->r_wid)) <= rad(0.0))
			ray->fov += rad(360.0);
		set_x_y_direction(ray);
		ray->i++;
	}
	del_list(&(p->spr), p);
}
