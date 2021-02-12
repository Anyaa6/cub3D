/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:43 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/03 15:50:40 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			error_0(int e_type)
{
	if (e_type == -1) //error on system call
		dprintf(1, "%s\n", strerror(errno));
	else if (e_type == 1)
		dprintf(1, "Map file reading process failed");
	else if (e_type == 2)
		dprintf(1, "Unreferenced element in map file");
	else if (e_type == 3)
		dprintf(1, "Wrong screen resolution input");
	else if (e_type == 4)
		dprintf(1, "Resolution input is negative");
	else if (e_type == 5)
		dprintf(1, "Wrong element name in map file");
	else if (e_type == 6)
		dprintf(1, "Wrong number of elements in map file");
	else if (e_type == 7)
		dprintf(1, "Map file does not end with .cub");
	else if (e_type == 8)
		dprintf(1, "Floor or ceiling color format wrong in map file");
	else if (e_type == 9)
		dprintf(1, "Multiple or no  player(s) on map");
	else if (e_type == 10)
		dprintf(1, "Map contains unreferenced char /!\\ tabs are not allowed");
}

void			error_1(int e_type)
{
	if (e_type == 11)
		dprintf(1, "The map is not closed");
	else if (e_type == 12)
		dprintf(1, "Image could not be loaded");
	else if (e_type == 13)
		dprintf(1, "Texture could not be loaded, possibly wrong path");
	else if (e_type == 14)
		dprintf(1, "Malloc issue while creating map");
	else if (e_type == 15)
		dprintf(1, "Too many or too few arguments to cub3D");
	else if (e_type == 16)
		dprintf(1, "Malloc issue while creating sprite");
	else if (e_type == 17)
		dprintf(1, "");
	else if (e_type == 18)
		dprintf(1, "");
	else if (e_type == 19)
		dprintf(1, "");
	else if (e_type == 20)
		dprintf(1, "");
}

void			error_2(int e_type)
{
	if (e_type == 21)
		dprintf(1, "");
	else if (e_type == 22)
		dprintf(1, "");
	else if (e_type == 23)
		dprintf(1, "");
	else if (e_type == 24)
		dprintf(1, "");
	else if (e_type == 25)
		dprintf(1, "");
	else if (e_type == 26)
		dprintf(1, "");
	else if (e_type == 27)
		dprintf(1, "");
	else if (e_type == 28)
		dprintf(1, "");
	else if (e_type == 29)
		dprintf(1, "");
	else if (e_type == 30)
		dprintf(1, "");
}

void			free_cub(t_cub3d *cub, int e_type)
{
	int         i;

	//rajouter des if pour ne pas risquer de free qqchose qui n'existe pas selon le stade de sortie de programme ou utiliser e_type : a partir de tel e_type, suppr ca, ca et ca mais pas ca car pas encore cree
	(void)e_type;//if e_type == 42 alors tout free
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
	//finir de free tous les pointeurs (chercher dans .h) et cree free_set_null pour les void *
}

//ajouter destroy window ici en fonction du msg d'erreur
void			free_memory(t_p *p, int e_type)
{
	free_cub(p->cub, e_type);
}

void			error(int e_type, t_p *p)
{
	dprintf(1, "Error\n");
	if (e_type <= 10)
		error_0(e_type);
	else if (e_type > 10 && e_type <= 20)
		error_1(e_type);
	else if (e_type > 20 && e_type <= 30)
		error_2(e_type);
	dprintf(1, "\n");
	free_memory(p, e_type);
	exit(EXIT_SUCCESS);
}
