/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_display_sprites.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:24:35 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/16 12:00:10 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//*spr = adresse que contient spr 
//**spr = le premier element que contient spr
//(*spr)-> equivaut a (**spr). donc c'est bien un double dereferencement

void            del_if_further(t_p *p, t_cubray *ray, t_cubspr **spr)
{
    t_cubspr        *to_remove;

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

void            set_start_stop_spr(t_p *p, t_cubspr *node)
{
    if (node->sp_hgt < p->cub->r_hgt)
    {
        node->yspr = 0.0;
        node->y0 = abs((p->cub->r_hgt - (int)floor(node->sp_hgt))) / 2;
    }
    else
    {
        node->yspr = ((node->sp_hgt - (float)(p->cub->r_hgt)) / 2) * node->step;
        node->y0 = 0;
    }
    node->yend = p->cub->r_hgt - node->y0;
}

t_cubspr	*new_node(t_p *p, double yf, double xf, double dist)
{
	t_cubspr		*node;

	if (!(node = (t_cubspr *)malloc(sizeof(t_cubspr))))
		error (16, p);
	node->next = NULL;
	node->i0 = p->ray->i;
	node->rays = 1;
	node->xf = xf;
	node->yf = yf;
	node->x = (int)floor(xf);
	node->y = (int)floor(yf);
	node->sp_dist = dist;
	node->sp_hgt = (p->ray->s_dist) / node->sp_dist;
	node->step = (float)p->img->imgs_h / node->sp_hgt;
	if (p->hv == 'h')
		node->hv = 'h';
	else if (p->hv == 'v')
		node->hv = 'v';
	node->xspr = 0.0;
	/*
	if (p->hv == 'v')
        node->xspr = 256.0 * modf(node->yf, &(p->ray->trash));
    else if (p->hv == 'h')
        node->xspr = 256.0 * modf(node->xf, &(p->ray->trash));
		*/
	set_start_stop_spr(p, node);
	return (node);
}

int			already_exists(t_cubspr *spr, t_p *p, double yf, double xf)
{
	int				x;
	int				y;

	x = (int)floor(xf);
	y = (int)floor(yf);
	while (spr)
	{
		if (spr->x == x && spr->y == y)
		{
			spr->xf = xf;//inutile mais pour se reperer
			spr->yf = yf;
			spr->rays++;
			return (1);
		}
		spr = spr->next;
	}
	spr = p->first;
	return (0);
}

int			dist_to_center(double yf, double xf, t_p *p)
{
	double			dist;

	xf = floor(xf) + 0.5;
	yf = floor(yf) + 0.5;
	//calcul de distance OK
	dist = sqrt(pow(fabs(xf - p->ray->x0), 2.0) + pow(fabs(yf - p->ray->y0), 2.0));
	//dprintf(1, "xf milieu = %.2f, yf milieu = %.2f, dist = %.2f\n", xf, yf, dist);
	//dist = fabs(fabs((xf - p->ray->x0)) / fabs(cos(p->ray->fov)));
	//dist = dist * fabs(cos(fabs(rad(p->cub->dir) - p->ray->fov))); 
	return (dist);
}

void		sort_insert_node(t_cubspr **spr, t_p *p, double  yf, double xf)
{
	double			dist;
	t_cubspr 		*tmp;

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
		while ((dist < (*spr)->sp_dist) && (*spr)->next && dist < (*spr)->next->sp_dist)
			*spr = (*spr)->next;
		tmp = (*spr)->next;
		(*spr)->next = new_node(p, yf, xf, dist);
		(*spr)->next->next = tmp;
	}
}

void		add_sprite(t_cubspr **spr, t_p *p, double yf, double xf)
{
	//dprintf(1, "p->ray->i = %d", p->ray->i);
	if (p->first)
		*spr = p->first;
	if (p->first && already_exists(*spr, p, yf, xf))
		return ;
	sort_insert_node(spr, p, yf, xf);
	*spr = p->first;
}

			//dprintf(1, "x = %d, spr->x = %d, y = %d, spr->y = %d\n", x, (spr)->x,  y, (spr)->y);
