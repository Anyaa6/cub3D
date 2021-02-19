/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:59:03 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/18 14:36:23 by abonnel          ###   ########lyon.fr   */
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
}

void			init_mlx(t_cub3d *cub)
{
	if ((cub->mlx_p = mlx_init()) == NULL)
		exit(-1);
	if ((cub->win_p = mlx_new_window(cub->mlx_p, cub->r_wid, cub->r_hgt, \
					"AB's cub")) == NULL)
		exit(-1);
}

int				exit_hook(t_p *p)
{
	free_memory(p, 42);
	mlx_destroy_window(p->cub->mlx_p, p->cub->win_p);
	exit(0);
}

int				key_release_hook(int keycode, t_p *p)
{
	if (keycode == 53)
	{
		mlx_destroy_window(p->cub->mlx_p, p->cub->win_p);
		free_memory(p, 42);
		exit(1);
	}
	else if (keycode == 13 || keycode == 1 \
			|| keycode == 125 || keycode == 126)//avancer W et reculer S
		move_front_back(keycode, p->cub);
	else if (keycode == 0) //Gauche A
		move_left(p->cub);
	else if (keycode == 2) // Droite D
		move_right(p->cub);
	else if (keycode == 123 || keycode == 124)
		rotation(keycode, p->cub);
	return (1);
}

int     key_press_hook(int keycode, t_p *p)
{
	mlx_do_key_autorepeaton(p->cub->mlx_p);
	if (keycode == 53)
	{
		mlx_destroy_window(p->cub->mlx_p, p->cub->win_p);
		free_memory(p, 42);
		exit(1);
	}
	else if (keycode == 13 || keycode == 1 \
			|| keycode == 125 || keycode == 126)//avancer W et reculer S
		move_front_back(keycode, p->cub);
	else if (keycode == 0) //Gauche A
		move_left(p->cub);
	else if (keycode == 2) // Droite D
		move_right(p->cub);
	else if (keycode == 123 || keycode == 124)
		rotation(keycode, p->cub);
	return (1);
}

void			event(t_cub3d *cub, t_p *p)//#include "X.h"
{
	mlx_do_key_autorepeatoff(cub->mlx_p);
	mlx_hook(cub->win_p, 2, 0, key_press_hook, p);
	mlx_hook(cub->win_p, 3, 0, key_release_hook, p);
	mlx_hook(cub->win_p, 17, 0, exit_hook, p);
}

//erreur si plus de 3 argc ? (map + --save)
int 			main(int argc, char **argv)
{
	t_cub3d		cub;
	t_cubimg	img;
	t_cubray	ray;
	t_p		p;

	if (argc < 2 || argc > 3)
		error(15, &p);
	init_cub_img(&cub, &img, &ray, &p);
	parsing_cub(argv[1], &p);
	init_mlx(&cub);
	//display(&p);
	event(&cub, &p);
	mlx_loop_hook (cub.mlx_p, &display, &p);
	mlx_loop(cub.mlx_p);//celle ci doit rester a la fin en dehors de toute boucle
	free_memory(&p, 42);//ne semble pas arriver jusqu'ici pour le moment
	return (0);
}
