/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:02:04 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 12:09:22 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init_cub_img(t_cub3d *cub, t_cubimg *img, t_cubray *ray, t_p *p)
{
	cub->mlx_p = NULL;
	cub->win_p = NULL;
	cub->r_wid = 0;
	cub->r_hgt = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->sp = NULL;
	cub->floor = 0;
	cub->top = 0;
	cub->map = NULL;
	cub->map_h = -1;
	cub->map_w = -1;
	img->x = 42;
	img->y = 42;
	p->cub = cub;
	p->img = img;
	p->ray = ray;
	ray->offset = 0;
	ray->xtxt = 0;
	p->spr = NULL;
	p->first = NULL;
	cub->fl_s = NULL;
	cub->top_s = NULL;
}

void			init_mlx(t_cub3d *cub)
{
	if ((cub->mlx_p = mlx_init()) == NULL)
		exit(-1);
	if ((cub->win_p = mlx_new_window(cub->mlx_p, cub->r_wid, cub->r_hgt, \
					"AB's cub")) == NULL)
		exit(-1);
}

void			init_img_sprite(t_cub3d *cub, t_cubimg *img, t_p *p)
{
	if ((img->p_sp = mlx_xpm_file_to_image(cub->mlx_p, cub->sp, &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
	img->sp_img = (int*)mlx_get_data_addr(img->p_sp, &img->txt_b, &img->txt_l, \
			&img->txt_e);
	if (cub->top_s != NULL)
	{
		if ((img->p_sk = mlx_xpm_file_to_image(cub->mlx_p, cub->top_s, \
						&img->imgs_w, &img->imgs_h)) == NULL)
			error(13, p);
		img->sk_img = (int*)mlx_get_data_addr(img->p_sk, &img->txt_b, \
				&img->txt_l, &img->txt_e);
	}
	if (cub->fl_s != NULL)
	{
		if ((img->p_fl = mlx_xpm_file_to_image(cub->mlx_p, cub->fl_s, \
						&img->imgs_w, &img->imgs_h)) == NULL)
			error(13, p);
		img->fl_img = (int*)mlx_get_data_addr(img->p_fl, &img->txt_b, \
				&img->txt_l, &img->txt_e);
	}
}

void			init_img_bonus(t_cub3d *cub, t_cubimg *img, t_p *p)
{
	if ((img->p_hu = mlx_xpm_file_to_image(cub->mlx_p, "./assets/xpm/HUD.xpm", \
					&img->imgs_w, &img->imgs_h)) == NULL)
		error(13, p);
	if ((img->p_lb = mlx_png_file_to_image(cub->mlx_p, \
					"./assets/xpm/lifebar.png", &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
}

void			init_imgs(t_cub3d *cub, t_cubimg *img, t_p *p)
{
	init_img_sprite(cub, img, p);
	init_img_bonus(cub, img, p);
	if ((img->p_no = mlx_xpm_file_to_image(cub->mlx_p, cub->no, &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
	img->no_img = (int*)mlx_get_data_addr(img->p_no, &img->txt_b, &img->txt_l, \
			&img->txt_e);
	if ((img->p_so = mlx_xpm_file_to_image(cub->mlx_p, cub->so, &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
	img->so_img = (int*)mlx_get_data_addr(img->p_so, &img->txt_b, &img->txt_l, \
			&img->txt_e);
	if ((img->p_ea = mlx_xpm_file_to_image(cub->mlx_p, cub->ea, &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
	img->ea_img = (int*)mlx_get_data_addr(img->p_ea, &img->txt_b, &img->txt_l, \
			&img->txt_e);
	if ((img->p_we = mlx_xpm_file_to_image(cub->mlx_p, cub->we, &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
	img->we_img = (int*)mlx_get_data_addr(img->p_we, &img->txt_b, &img->txt_l, \
			&img->txt_e);
	img->txt_l /= 4;
}
