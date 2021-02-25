/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:59:03 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 14:04:29 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				exit_hook(t_p *p)
{
	free_memory(p);
	return (1);
}

int				key_release_hook(int keycode, t_p *p)
{
	if (keycode == 53)
		free_memory(p);
	else if (keycode == 13 || keycode == 1 \
			|| keycode == 125 || keycode == 126)
		move_front_back(keycode, p->cub);
	else if (keycode == 0)
		move_left(p->cub);
	else if (keycode == 2)
		move_right(p->cub);
	else if (keycode == 123 || keycode == 124)
		rotation(keycode, p->cub);
	return (1);
}

int				key_press_hook(int keycode, t_p *p)
{
	mlx_do_key_autorepeaton(p->cub->mlx_p);
	if (keycode == 53)
		free_memory(p);
	else if (keycode == 13 || keycode == 1 \
			|| keycode == 125 || keycode == 126)
		move_front_back(keycode, p->cub);
	else if (keycode == 0)
		move_left(p->cub);
	else if (keycode == 2)
		move_right(p->cub);
	else if (keycode == 123 || keycode == 124)
		rotation(keycode, p->cub);
	return (1);
}

void			event(t_cub3d *cub, t_p *p)
{
	mlx_do_key_autorepeatoff(cub->mlx_p);
	mlx_hook(cub->win_p, 2, 0, key_press_hook, p);
	mlx_hook(cub->win_p, 3, 0, key_release_hook, p);
	mlx_hook(cub->win_p, 17, 0, exit_hook, p);
}

int				main(int argc, char **argv)
{
	t_cub3d		cub;
	t_cubimg	img;
	t_cubray	ray;
	t_p			p;

	if (argc < 2 || argc > 3)
		error(20, &p);
	init_cub_img(&cub, &img, &ray, &p);
	parsing_cub(argv[1], &p);
	init_mlx(&cub);
	init_imgs(p.cub, p.img, &p);
	if (argc == 3)
		save_bmp(&p, argv[2]);
	event(&cub, &p);
	mlx_loop_hook(cub.mlx_p, &display, &p);
	mlx_loop(cub.mlx_p);
	return (0);
}
