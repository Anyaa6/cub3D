/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writinginimage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:42:30 by abonnel           #+#    #+#             */
/*   Updated: 2021/01/25 16:42:38 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// screen resolution x = 600 y = 400
// offset si img_str caste en int * : x + y * line_size / 4;

void	texture_to_img(int x, int y, int xpm_l_size, int line_size, int *xpm, int *img)
{
	int		xbis = x;
	int		ybis = y;
	int		i = 0;

	while (y < ybis + (xpm_l_size / 4))
	{
		while (x < xbis + (xpm_l_size / 4))
		{
			img[x + y * (line_size / 4)] = xpm[i];
			x++;
			i++;
		}
		x = xbis;
		y++;
	}

}

//trapeze(350, xpm_l_size, line_size, 200, 600, xpm, img);

void	trapeze(int x, int xpm_l_size, int line_size, int w_size, int xmax, int *xpm, int *img)
{
	int		i = 0;
	// y = moitie de l'ecran - moitie de taille
	// y = y_res / 2 - w_size / 2
	int		y = (400 / 2) - (w_size / 2); // 200 - 100 = 100
	int		ymax = (400 / 2) + (w_size / 2); // 200 + 100 = 300
	int		ybis = y;
	int		tour = 0;
	
	while (x < xmax)
	{
		while (y < ymax)
		{
			if (i >= ((xpm_l_size * xpm_l_size) / 16))
				i = 0;
			img[x + y * (line_size / 4)] = xpm[i];
			y++;
			i++;
		}
		x++;
		y = ybis + (tour * 1);
		tour++;
		ymax--;
	}
}

int		test(void *mlx_ptr, void *win_ptr)//initialisations
{
	void *empty_img;

	empty_img = mlx_new_image(mlx_ptr, 600, 400);

	int 	*img;
	int		bits;
	int		line_size;
	int		endian;

	img = (int *)mlx_get_data_addr(empty_img, &bits, &line_size, &endian);
	printf("empty img :\nbits = %d, line_size = %d, endian = %d\n", bits, line_size, endian);	

	void	*xpm_img;
	int		height;
	int		width;

	xpm_img = mlx_xpm_file_to_image(mlx_ptr, "../brouillonscub3d/assets/screw64.xpm", &width, &height);

	int		*xpm;
	int		xpm_bits;
	int		xpm_l_size;

	xpm = (int*)mlx_get_data_addr(xpm_img, &xpm_bits, &xpm_l_size, &endian);
	printf("xpm : \nbits = %d, line_size = %d, endian = %d\n", xpm_bits, xpm_l_size, endian);	

	// fonctions de transfert d'info de texture a image vide

	texture_to_img(200, 300, xpm_l_size, line_size, xpm, img);
	texture_to_img(500, 300, xpm_l_size, line_size, xpm, img);

	int		x = 0;
	int		w_size = 300;
	int		xmax = 100;

	trapeze(x, xpm_l_size, line_size, w_size, xmax, xpm, img);
	trapeze(350, xpm_l_size, line_size, 200, 600, xpm, img);

	

	mlx_put_image_to_window(mlx_ptr, win_ptr, empty_img, 0, 0);
	return (1);
}


/*
   void *
   mlx_new_image ( void *mlx_ptr, int width, int height );

   char *
   mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line,
   int *endian );

   int
   mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void  *img_ptr,
   int x, int y );

   unsigned int
   mlx_get_color_value ( void *mlx_ptr, int color );
   */

int 	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	//void	*p;

	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	if ((win_ptr = mlx_new_window(mlx_ptr, 600, 400, "abonnel's cub3D")) == NULL)
		return (0);
	test(mlx_ptr, win_ptr);
	mlx_loop(mlx_ptr);
	return (0);
}
