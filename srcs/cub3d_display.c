/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:04:38 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/12 10:07:07 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// offset si img_str caste en int * : x + y * line_size / 4;

void		init_img_sprite(t_cub3d *cub, t_cubimg *img, t_p *p)
{
	if ((img->p_img = mlx_new_image(cub->mlx_p, cub->r_wid, cub->r_hgt)) \
			== NULL)
		error(12, p);
	img->img = (int *)mlx_get_data_addr(img->p_img, &img->bits, &img->lsize, \
			&img->endian);
	img->lsize /= 4;
	if ((img->p_sp = mlx_xpm_file_to_image(cub->mlx_p, cub->sp, &img->imgs_w, \
					&img->imgs_h)) == NULL)
		error(13, p);
	img->sp_img = (int*)mlx_get_data_addr(img->p_sp, &img->txt_b, &img->txt_l, \
			&img->txt_e); 
	//rajouter une ligne pour determiner d'emblee la valeur des pixels rose a ne pas afficher?
}

//lsize / 4 car tableau caste en int
void		init_imgs(t_cub3d *cub, t_cubimg *img, t_p *p)
{
	init_img_sprite(cub, img, p);
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

void		draw_top_floor(t_cub3d *cub, t_cubimg *img)
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

int			display(t_p *p)
{
	init_imgs(p->cub, p->img, p);
	draw_top_floor(p->cub, p->img);
	raycasting(p->cub, p->img, p->ray, p);
	mlx_put_image_to_window(p->cub->mlx_p, p->cub->win_p, p->img->p_img, 0, 0);
	return (1);
}
