/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:04:38 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 13:54:03 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_top(t_cub3d *cub, t_cubimg *img)
{
	int				x;
	int				y;

	x = 0;
	y = 0;
	while (y < cub->r_hgt / 2)
	{
		while (x < cub->r_wid)
		{
			img->img[x + y * img->lsize] = cub->top;
			x++;
		}
		y++;
		x = 0;
	}
}

void		draw_floor(t_cub3d *cub, t_cubimg *img)
{
	int				x;
	int				y;

	y = cub->r_hgt / 2;
	x = 0;
	while (y < cub->r_hgt)
	{
		while (x < cub->r_wid)
		{
			img->img[x + y * img->lsize] = cub->floor;
			x++;
		}
		y++;
		x = 0;
	}
}

void		top_txt(t_cub3d *cub, t_cubimg *img)
{
	int				x;
	int				y;
	int				xtxt;
	int				ytxt;

	y = 0;
	x = 0;
	ytxt = 0;
	xtxt = 0;
	while (y < cub->r_hgt / 2)
	{
		while (x < cub->r_wid)
		{
			img->img[x + y * img->lsize] = img->sk_img[xtxt + ytxt * \
				img->txt_l];
			xtxt = ++x % 255;
		}
		ytxt = ++y % 255;
		x = 0;
		xtxt = 0;
	}
}

void		fl_txt(t_cub3d *cub, t_cubimg *img)
{
	int				x;
	int				y;
	int				xtxt;
	int				ytxt;

	y = cub->r_hgt / 2;
	x = 0;
	ytxt = 0;
	xtxt = 0;
	while (y < cub->r_hgt)
	{
		while (x < cub->r_wid)
		{
			img->img[x + y * img->lsize] = \
				img->fl_img[xtxt + ytxt * img->txt_l];
			xtxt = ++x % 255;
		}
		ytxt = ++y % 255;
		x = 0;
		xtxt = 0;
	}
}

int			display(t_p *p)
{
	new_img(p->cub, p->img, p);
	if (p->cub->top_s == NULL)
		draw_top(p->cub, p->img);
	else
		top_txt(p->cub, p->img);
	if (p->cub->fl_s == NULL)
		draw_floor(p->cub, p->img);
	else
		fl_txt(p->cub, p->img);
	raycasting(p->cub, p->img, p->ray, p);
	mlx_put_image_to_window(p->cub->mlx_p, p->cub->win_p, p->img->p_img, 0, 0);
	if (p->cub->r_wid > 231 && p->cub->r_hgt > 91)
		mlx_put_image_to_window(p->cub->mlx_p, p->cub->win_p, p->img->p_lb, \
				p->cub->r_wid - 230, p->cub->r_hgt - 50);
	if (p->cub->r_wid > 231 && p->cub->r_hgt > 35)
		mlx_put_image_to_window(p->cub->mlx_p, p->cub->win_p, p->img->p_hu, \
				10, 10);
	return (1);
}
