/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:13:59 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 14:35:19 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_save(t_save *save, t_p *p, char *head)
{
	save->file_size = 54 + (p->cub->r_wid * p->cub->r_hgt) * 4;
	save->offset = 54;
	save->dib_size = 40;
	save->planes = 1;
	save->b_per_pixel = 32;
	save->img_size = (p->cub->r_wid * p->cub->r_hgt) * 4;
	ft_memset(head, 0, 54);
	ft_memmove(head, "BM", 2);
	ft_memmove(head + 2, &save->file_size, 4);
	ft_memmove(head + 10, &save->offset, 4);
	ft_memmove(head + 14, &save->dib_size, 4);
	ft_memmove(head + 18, &p->cub->r_wid, 4);
	ft_memmove(head + 22, &p->cub->r_hgt, 4);
	ft_memmove(head + 26, &save->planes, 4);
	ft_memmove(head + 28, &save->b_per_pixel, 4);
	ft_memmove(head + 34, &save->img_size, 4);
}

void		set_res(t_p *p)
{
	if (p->cub->r_wid < 128)
		p->cub->r_wid = 128;
	else
		p->cub->r_wid = p->cub->r_wid / 64 * 64;
	if (p->cub->r_hgt < 128)
		p->cub->r_hgt = 128;
	else
		p->cub->r_hgt = p->cub->r_hgt / 64 * 64;
}

void		save_bmp(t_p *p, char *argv)
{
	int			fd;
	char		*head;
	t_save		save;
	int			i;

	if (ft_memcmp(argv, "--save", 6) != 0)
		error(16, p);
	fd = open("awesome.bmp", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (!(head = (char *)malloc(sizeof(char) * 54)))
		error(-1, p);
	set_res(p);
	set_save(&save, p, head);
	write(fd, head, 54);
	display(p);
	i = p->cub->r_hgt;
	while (i != 0)
	{
		write(fd, p->img->img + (i * p->cub->r_wid), p->cub->r_wid * 4);
		i--;
	}
	close(fd);
	free_memory(p);
}
