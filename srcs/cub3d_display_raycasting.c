/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_raycasting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:20:45 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 09:36:48 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/* Bien penser a la virgule dans le 180.0 sinon division d'entiers
   les fonctions de math utilisent les radians
   Radian = degre * (pi /180.0) // degre = radian * (180.0 / pi)
   la resolution est la taille de l'ecran donc tous les calculs en decoulent
   - distance oeil -> ecran = (r_wid / 2) / tan(30 * pi / 180)
   - res par defaut 320 * 200
   */

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

void			draw_sprite(t_cubspr *spr, t_cubimg *img)
{
	int				y0;
	double			yspr;

	if (spr->x_step >= 0.5)
		return;
	yspr = spr->yspr;
	y0 = spr->y0;
	while (spr->y0 < spr->yend)//boucle du y de l'img && xspr < 255?
	{
		if (img->sp_img[(int)round(spr->xspr) + (int)round(spr->yspr) * img->txt_l] != img->sp_img[0])
			img->img[spr->i0 + (spr->y0 * img->lsize) ] = img->sp_img[(int)round(spr->xspr) + (int)round(spr->yspr) * img->txt_l];
		spr->y0++;
		spr->yspr += spr->step;
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
		if ((ray->xtxt + (((int)round(ytxt)) * img->txt_l)) >= img->imgs_h * img->imgs_w)
			ytxt = 0.0;
		img->img[x + (img->y * img->lsize)] = (*ray->txt)[ray->xtxt + (((int)round(ytxt)) * img->txt_l)];
		img->y++;
		ytxt += step;
	}
	while (p->spr)
	{
		if (p->spr->sp_dist < p->ray->w_dist)
			draw_sprite(p->spr, p->img);
		p->spr = p->spr->next;
	}
	//dprintf(1, "img->y = %d, stop = %d, wall hgt = %.2f\n", img->y,stop, ray->w_hgt);
}

void			raycasting(t_cub3d *cub, t_cubimg *img, t_cubray *ray, t_p *p)
{
	init_ray_struct(cub, ray);
	ray->i = 0;
	while (ray->i < cub->r_wid)//chaque rayon
	{
		find_wall_height(p, ray);
		draw(ray->i, p, img, ray);
		if ((ray->fov -= rad(60.0 / (float)cub->r_wid)) <= rad(0.0))
			ray->fov += rad(360.0);
		set_x_y_direction(ray);
		ray->i++;
	}
	//display_list(p->spr, p);
	del_list(&(p->spr), p);
}

//voir ce au'il se passe quand FOV = 90 ou 180 ou 270...
// il faudra garder la valeur du dernier x pour avoir une image qui reprendra a la meme colonne du mur
//dprintf(1, "spr->xf = %.2f, spr->yf = %.2f, xspr = %d\n", p->spr->xf, p->spr->yf, p->spr->xspr);
/*
   if (p->hv == 'v')
   p->spr->xspr = 256 * modf(p->spr->yf, &(p->ray->trash));
   else if (p->hv == 'h')
   p->spr->xspr = 256 * modf(p->spr->xf, &(p->ray->trash));
   */	

