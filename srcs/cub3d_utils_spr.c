/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:08:29 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/19 13:14:40 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		display_list(t_cubspr *spr, t_p *p)
{
	spr = p->first;
	while (spr)
	{
		printf("\n=============================================\n");
		printf("i0 = %d\n", spr->i0);
		printf("x0 = %.2f ", p->ray->x0);
		printf("y0 = %.2f\n", p->ray->y0);
		printf("x = %d ", spr->x);
		printf("y = %d ", spr->y);
		printf("xf = %.2f ", spr->xf);
		printf("yf = %.2f\n", spr->yf);
		printf("sp_dist = %.2f ", spr->sp_dist);
		printf("w_dist = %.2f \n", p->ray->w_dist);
		printf("sp_hgt = %.2f ", spr->sp_hgt);
		printf("step = %.2f ", spr->step);
		printf("xspr = %.2f ", spr->xspr);
		printf("next = %p\n", spr->next);
		printf("\n=============================================\n");
		spr = spr->next;
	}
	spr = p->first;
}

void		del_list(t_cubspr **spr, t_p *p)
{
	t_cubspr		*tmp;

	*spr = p->first;
	while (*spr)
	{
		tmp = *spr;
		*spr = (*spr)->next;
		free(tmp);
	}
	p->first = NULL;
}
