/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:42:26 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/16 11:18:12 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			skip_space(char *s)
{
	int				i;

	i = 0;
	while (s[i] == ' ' && s[i])
		i++;
	return (i);
}

void		clean_map(t_cub3d *cub)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (cub->map[y])
	{
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == '1' || cub->map[y][x] == '0' \
					|| cub->map[y][x] == '2')
				cub->map[y][x] = ' ';
			x++;
		}
		y++;
		x = 0;
	}
	//en partant de la fin, while espace -> \0 et ensuite while 1 0 ou 2 transformer en espace
}

// mode : si 1 alors effacer les char inutiles. si 0 juste display map
void		display_map(t_cub3d *cub)
{
	int		y;

	y = 0;
	while (cub->map[y])
	{
		printf("%s\n", cub->map[y]);
		y++;
	}
	printf("\n");
}

double			rad(double degrees)
{
	double			radians;

	return (radians = degrees * (M_PI / 180.0));
}

double			deg(double radians)
{
	double			degrees;

	return (degrees = radians * (180.0 / M_PI));
}

void			display_list(t_cubspr *spr, t_p *p)
{
	spr = p->first;
	while (spr)
	{
		dprintf(1, "\n=============================================\n");
		dprintf(1, "i0 = %d\n", spr->i0);
		dprintf(1, "x0 = %.2f ", p->ray->x0); 
		dprintf(1, "y0 = %.2f\n", p->ray->y0);
		dprintf(1, "x = %d ", spr->x);
		dprintf(1, "y = %d ", spr->y);
		dprintf(1, "xf = %.2f ", spr->xf);
		dprintf(1, "yf = %.2f\n", spr->yf);
		dprintf(1, "sp_dist = %.2f ", spr->sp_dist); 
		dprintf(1, "w_dist = %.2f \n", p->ray->w_dist); 
		dprintf(1, "sp_hgt = %.2f ", spr->sp_hgt);
		dprintf(1, "step = %.2f ", spr->step);
		dprintf(1, "xspr = %.2f ", spr->xspr);
		dprintf(1, "next = %p\n", spr->next);
		dprintf(1, "\n=============================================\n");
		spr = spr->next; 
	}
	//spr = p->first;
}

void			del_list(t_cubspr **spr, t_p *p)
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
