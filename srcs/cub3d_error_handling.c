/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:43 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 14:19:40 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			error_0(int e_type)
{
	if (e_type == -1)
		printf("%s\n", strerror(errno));
	else if (e_type == 1)
		printf("Map file reading process failed");
	else if (e_type == 2)
		printf("Unreferenced element in map file");
	else if (e_type == 3)
		printf("Wrong screen resolution input");
	else if (e_type == 4)
		printf("Resolution input is negative");
	else if (e_type == 5)
		printf("Wrong element name in map file");
	else if (e_type == 6)
		printf("Wrong number of elements in map file");
	else if (e_type == 7)
		printf("Map file does not end with .cub");
	else if (e_type == 8)
		printf("Floor or ceiling color format wrong in map file");
	else if (e_type == 9)
		printf("Multiple or no  player(s) on map");
	else if (e_type == 10)
		printf("Map contains unreferenced char /!\\ tabs are not allowed");
}

void			error_1(int e_type)
{
	if (e_type == 11)
		printf("The map is not closed");
	else if (e_type == 12)
		printf("Image could not be loaded");
	else if (e_type == 13)
		printf("Texture could not be loaded, possibly wrong path");
	else if (e_type == 14)
		printf("Malloc issue while creating map");
	else if (e_type == 15)
		printf("Malloc issue while creating sprite");
	else if (e_type == 16)
		printf("The second argument can only be \"--save\"");
	else if (e_type == 17)
		printf("");
	else if (e_type == 18)
		printf("");
	else if (e_type == 19)
		printf("");
	else if (e_type == 20)
		printf("Too many or too few arguments to cub3");
}

void			free_cub(t_cub3d *cub)
{
	int			i;

	if (cub->win_p)
		mlx_destroy_window(cub->mlx_p, cub->win_p);
	i = 0;
	if (cub->map == NULL)
		return ;
	else
	{
		while (cub->map[i] != NULL)
			free_set_null(&cub->map[i++]);
		free_set_null(&cub->map[i]);
		free_set_null(cub->map);
	}
	free_set_null(&cub->no);
	free_set_null(&cub->so);
	free_set_null(&cub->we);
	free_set_null(&cub->ea);
	free_set_null(&cub->sp);
	free_set_null(&cub->fl_s);
	free_set_null(&cub->top_s);
}

void			free_memory(t_p *p)
{
	if (p->img->p_img)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_img);
	if (p->img->p_no)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_no);
	if (p->img->p_ea)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_ea);
	if (p->img->p_we)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_we);
	if (p->img->p_so)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_so);
	if (p->img->p_sp)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_sp);
	if (p->img->p_sk)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_sk);
	if (p->img->p_fl)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_fl);
	if (p->img->p_hu)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_hu);
	if (p->img->p_lb)
		mlx_destroy_image(p->cub->mlx_p, p->img->p_lb);
	if (p->cub->win_p)
		mlx_clear_window(p->cub->mlx_p, p->cub->win_p);
	free_cub(p->cub);
	exit(EXIT_SUCCESS);
}

void			error(int e_type, t_p *p)
{
	printf("Error\n");
	if (e_type <= 10)
		error_0(e_type);
	else if (e_type > 10 && e_type <= 20)
		error_1(e_type);
	printf("\n");
	free_memory(p);
}
