/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_sprites.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:24:35 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 13:52:39 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			del_if_further(t_p *p, t_cubray *ray, t_cubspr **spr)
{
	t_cubspr			*to_remove;

	(*spr) = p->first;
	if ((*spr)->sp_dist >= ray->w_dist)
	{
		to_remove = *spr;
		*spr = (*spr)->next;
		p->first = *spr;
		free(to_remove);
	}
	else
	{
		while ((*spr)->next)
		{
			if ((*spr)->next->sp_dist >= ray->w_dist)
			{
				to_remove = (*spr)->next;
				if ((*spr)->next->next)
					(*spr)->next = (*spr)->next->next;
				free(to_remove);
			}
			(*spr) = (*spr)->next;
		}
	}
	(*spr) = p->first;
}

t_cubspr		*new_node(t_p *p, double yf, double xf, double dist)
{
	t_cubspr			*node;

	if (!(node = (t_cubspr *)malloc(sizeof(t_cubspr))))
		error(15, p);
	node->next = NULL;
	node->i0 = p->ray->i;
	node->xf = xf;
	node->yf = yf;
	node->x = (int)floor(xf);
	node->y = (int)floor(yf);
	node->sp_dist = dist;
	node->sp_hgt = (p->ray->s_dist) / node->sp_dist;
	node->step = (float)p->img->imgs_h / node->sp_hgt;
	node->xspr = 0.0;
	set_start_stop_spr(p, node);
	mesures_to_sprcenter(p, node);
	xspr_step(p, node);
	return (node);
}

int				already_exists(t_cubspr *spr, t_p *p, double yf, double xf)
{
	int					x;
	int					y;

	x = (int)floor(xf);
	y = (int)floor(yf);
	while (spr)
	{
		if (spr->x == x && spr->y == y)
		{
			spr->xf = xf;
			spr->yf = yf;
			spr->i0 = p->ray->i;
			xspr_step(p, spr);
			return (1);
		}
		spr = spr->next;
	}
	spr = p->first;
	return (0);
}

void			sort_insert_node(t_cubspr **spr, t_p *p, double yf, double xf)
{
	double				dist;
	t_cubspr			*tmp;

	dist = dist_to_center(yf, xf, p);
	if (!(*spr) || dist >= (*spr)->sp_dist)
	{
		tmp = *spr;
		*spr = new_node(p, yf, xf, dist);
		(*spr)->next = tmp;
		p->first = *spr;
	}
	else
	{
		while ((dist < (*spr)->sp_dist) && (*spr)->next && \
				dist < (*spr)->next->sp_dist)
			*spr = (*spr)->next;
		tmp = (*spr)->next;
		(*spr)->next = new_node(p, yf, xf, dist);
		(*spr)->next->next = tmp;
	}
}

void			add_sprite(t_cubspr **spr, t_p *p, double yf, double xf)
{
	if (p->first)
		*spr = p->first;
	if (p->first && already_exists(*spr, p, yf, xf))
		return ;
	sort_insert_node(spr, p, yf, xf);
	*spr = p->first;
}
