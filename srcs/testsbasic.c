/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testsbasic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:22:27 by abonnel           #+#    #+#             */
/*   Updated: 2021/01/28 14:35:10 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 ** well formated comment
 */

/* Pour png :

	void	*png_ptr;
	// pointer to png file
	png_ptr = mlx_png_file_to_image(mlx_ptr, "assets/pattern.png", &width, &height);
	printf("width = %d, height = %d\n", width, height);

	mlx_put_image_to_window(mlx_ptr, win_ptr, png_ptr, 0, 30);
	mlx_put_image_to_window(mlx_ptr, win_ptr, png_ptr, 374, 30);
*/

int		test(void *mlx_ptr, void *win_ptr)
{
	int		x;
	void	*xpm_ptr;
	int		height;
	int		width;

	//draw 2 horizontal lines of  diff shades of pink
	x = 10;
	while (x++ < 300)
		mlx_pixel_put(mlx_ptr, win_ptr, x, 10, 16716947);
	x = 50;
	while (x++ < 300)
		mlx_pixel_put(mlx_ptr, win_ptr, x, 20, 16738740);
	// smth drawn after another will come on top -> useful for ceiling and floor,

	//pointer to xpm file, width and height are filed in by function
	xpm_ptr = mlx_xpm_file_to_image(mlx_ptr, "assets/xpm/ea.xpm", &width, &height);
	printf("width = %d, height = %d\n\n", width, height);

	// get ptr to image and then draw img on window
//	mlx_put_image_to_window(mlx_ptr, win_ptr, xpm_ptr, 0, 200);

	//create new empty image
	void	*new_img_ptr;
	new_img_ptr = mlx_new_image(mlx_ptr, 64, 64);

	//makes a string out of the empty image that we can fill with colors
	char	*new_img_str;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	new_img_str = mlx_get_data_addr(xpm_ptr, &bits_per_pixel, &size_line, &endian); 
	//printf("bits_per_pixel = %d donc 4 x 8 soit la taille d'un int ou d'un unsigned int\nsize_line = %d, endian = %d\n", bits_per_pixel, size_line, endian);

	// string out of the xpm file 
	char	*img_str;
	img_str = mlx_get_data_addr(new_img_ptr, &bits_per_pixel, &size_line, &endian); 
	//printf("bits_per_pixel = %d donc 4 x 8 soit la taille d'un int ou d'un unsigned int\nsize_line = %d, endian = %d\n", bits_per_pixel, size_line, endian);

   	//printf("size of unsigned int = %lu and of int = %lu\n", sizeof(unsigned int), sizeof(int));	

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

int		key_hook(int keycode, void *p)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 53)
		exit(1);
	(void)p;
	return (1);
}

int 	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		(*key)(int, void *);
	//void	*p;

	// initialize connexion to graphic server
	if ((mlx_ptr = mlx_init()) == NULL)
		return (0);
	// initialize and identify new window 
	if ((win_ptr = mlx_new_window(mlx_ptr, 600, 600, "abonnel's cub3D")) == NULL)
		return (0);
	test(mlx_ptr, win_ptr);
	// Opens window and handles its drawing/display + events
	key = &key_hook;
	while (mlx_key_hook(win_ptr, key, NULL))
	{
		
	}
	mlx_loop(mlx_ptr);
	return (0);
}

/*
   KEYCODES

   esc = 53
   fleche gauche = 123
   fleche haut = 126
   fleche droite = 124
   fleche bas = 125
   W = 13
   A = 0
   S = 1
   D = 2
   */


/*
void        display_top_floor(t_cub3d *cub, t_cubimg *img)
{
    int             x;
    int             y;

    x = -1;
    y = 0;
    while (y < cub->r_hgt / 2)
    {
        while (x++ < cub->r_wid)
            mlx_pixel_put(cub->mlx_p, cub->win_p, x, y, cub->top);
        y++;
        x = 0;
    }
    while (y < cub->r_hgt)
    {
        while (x < cub->r_wid)
        {
            mlx_pixel_put(cub->mlx_p, cub->win_p, x, y, cub->floor);
            x++;
        }
        y++;
        x = 0;
    }
}*/
