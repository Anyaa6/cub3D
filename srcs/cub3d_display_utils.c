/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:57:27 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 13:57:16 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			find_next_xy_h(t_cubray *ray, double xa, double ya)
{
	if (ray->y_dir > 0)
		ray->yh += ya;
	else
		ray->yh -= ya;
	if (ray->x_dir > 0)
		ray->xh += xa;
	else
		ray->xh -= xa;
}

void			find_next_xy_v(t_cubray *ray, double xa, double ya)
{
	if (ray->y_dir > 0)
		ray->yv += ya;
	else
		ray->yv -= ya;
	if (ray->x_dir > 0)
		ray->xv += xa;
	else
		ray->xv -= xa;
}

void			new_img(t_cub3d *cub, t_cubimg *img, t_p *p)
{
	if ((img->p_img = mlx_new_image(cub->mlx_p, cub->r_wid, cub->r_hgt)) \
			== NULL)
		error(12, p);
	img->img = (int *)mlx_get_data_addr(img->p_img, &img->bits, &img->lsize, \
			&img->endian);
	img->lsize /= 4;
}
