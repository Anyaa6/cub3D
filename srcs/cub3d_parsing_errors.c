/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 09:27:15 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/26 10:01:52 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_res_input(char *line, int size, t_p *p)
{
	int				size_len;
	int				r_len;

	while (*line == ' ')
		line++;
	if (*line == '-')
		error(4, p);
	size_len = 1;
	while (size >= 10)
	{
		size /= 10;
		size_len++;
	}
	r_len = 0;
	while (ft_isdigit(line[r_len]))
		r_len++;
	if (r_len > size_len)
		return (1);
	return (0);
}

void		parsing_error(char *argv1, char *line, t_p *p)
{
	int				av_l;

	av_l = ft_strlen(argv1);
	if (!(argv1[--av_l] == 'b' && argv1[--av_l] == 'u' && argv1[--av_l] == 'c' \
				&& argv1[--av_l] == '.'))
		error(7, p);
	if (!ft_isdigit(*line) && *line != ' ')
		error(1, p);
}

int			check_each_triplets(char *line, int *i, int digit_nb, int triplet)
{
	while (ft_isdigit(line[*i]) && line[*i])
	{
		*i += 1;
		digit_nb++;
	}
	if (digit_nb > 3 || digit_nb < 1)
		return (1);
	if (triplet < 2)
	{
		if (line[*i] == ',' && line[*i + 1])
			*i += 1;
		else
			return (1);
	}
	return (0);
}

int			check_floor_ceiling_clr_input(char *line)
{
	int				digit_nb;
	int				i;
	int				triplet;

	i = skip_space(line + 1) + 1;
	digit_nb = 0;
	triplet = 0;
	while (line[i])
	{
		if (check_each_triplets(line, &i, digit_nb, triplet) == 1)
			return (1);
		triplet++;
	}
	return (0);
}
