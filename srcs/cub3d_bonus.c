/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:37:02 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 13:54:43 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sky_floor_texture(t_cub3d *cub, char *line)
{
	if (line[0] == 'F')
		cub->fl_s = ft_strdup((line + 1 + skip_space(line + 1)));
	else
		cub->top_s = ft_strdup((line + 1 + skip_space(line + 1)));
}
