/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:15:30 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/18 15:20:10 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
// supprimer les printf

typedef	struct	s_cub3d
{
	void				*mlx_p;
	void				*win_p;
	int					r_wid;
	int					r_hgt;
	char				*no; //chemin par rapport a a.out
	char				*so;
	char				*ea;
	char				*we;
	char				*sp;
	unsigned int		floor;
	unsigned int		top;
	char				**map;
	int					map_w;//longueurs donc si index enlever 1
	int					map_h;//longueurs donc si index enlever 1
	char				dir_start;
	int					xstart;
	int					ystart;
	double				x0;
	double				y0;
	double				dir; // angle en DEGRES 
}				t_cub3d;

typedef struct	s_cubimg //enlever les endian??
{
	int					x;
	int					y;
	void				*p_img;
	int					*img;
	int					bits;//32
	int					lsize;//size ont ete toutes divisees par 4 soit 256 (1026/4)
	int					endian;
	void				*p_no;
	int					*no_img;
	void				*p_ea;
	int					*ea_img;
	void				*p_we;
	int					*we_img;
	void				*p_so;
	int					*so_img;
	void				*p_sp;
	int					*sp_img;
	int					imgs_h;//256
	int					imgs_w;//256
	int					txt_b;//32
	int					txt_l;//256 (1026 si sous forme de tableau de char)
	int					txt_e;//0
}				t_cubimg;

typedef struct	s_cubray {
	double				x0;//pos joueur
	double				y0;//pos joueur
	double				xv;
	double				yv;
	double				xh;
	double				yh;
	double				x;//valeur finale de x pour le wall le plus proche
	double				y;//valeur finale de x pour le wall le plus proche
	int					v;
	int					h;
	int					x_dir;
	int					y_dir;
	double				fov;//en radians
	double				eye_h;
	double				s_dist;
	double				w_dist;
	double				w_hgt;
	int					**txt;//pointeur vers texture a afficher selon NSWE
	int					offset;
	int					xtxt;
	int					i;
	double				trash;//pour partie integral
}				t_cubray;

typedef struct	s_cubspr {
	int					x;
	int					y;
	double				xf;
	double				yf;
	double				sp_dist;
	double				sp_hgt;
	double				step;
	double				x_step;
	int					i0;//numero du premier rayon q touche spr
	int					y0;//y pour img[]
	int					yend;
	double				xspr;
	double				yspr;
	double				dx;//delta de x au centre du sprite
	double				dy;
	double				delta;//angle a la droite passant par milieu du sprite
	double				cdel;
	double				beta;//angle interne entre alpha et delta
	char				hv;
	struct s_cubspr		*next;
}				t_cubspr;
	

typedef struct	s_p {
	t_cub3d				*cub;
	t_cubimg			*img;
	t_cubray			*ray;
	t_cubspr			*spr;//set a NULL a l'init
	t_cubspr			*first;//set a NULL a l'init
	char				hv;
}				t_p;

# include <math.h>
# include <unistd.h> //write, close, read
# include <stdlib.h>//exit, malloc, free
# include <errno.h> //errno -> pas dans subject mais obligatoire pour perror strerror
# include <stdio.h> //perror et printf
# include <string.h> //strerror
# include <fcntl.h> //open
# include "../minilibx_mms_20200219/mlx.h"
# include "../libft_gnl_git/libft.h"
# include "../libft_gnl_git/gnl/get_next_line.h"

// main.c


// cub3d_utils.c

int					skip_space(char *s);
void				display_map(t_cub3d *cub);
void				clean_map(t_cub3d *cub);
double				rad(double degrees);
double				deg(double radians);
void				display_list(t_cubspr *spr, t_p *p);
void				del_list(t_cubspr **spr, t_p *p);

// cub3d_parsing.c

void				parsing_cub(char *argv1, t_p *p);
void				graphic_specs(t_cub3d *cub, char *line, t_p *p);
void				get_resolution(t_cub3d *cub, char *line, t_p *p);
void				floor_ceiling_color(t_cub3d *cub, char *line, int i, t_p *p);
void				elements_path(t_cub3d *cub, char *line, int i);

// cub3d_map.c
void				get_map(int fd, t_p *p, char *line);
void				find_player_start(t_cub3d *cub, t_p *p);

// cub3d_closed_map.c
void				map_is_closed(t_cub3d *cub, t_p *p);

// cub3d_parsing_errors.c
int					check_res_input(char *line, int size, t_p *p);
void				parsing_error(char *argv1, char *line, t_p *p);
int					check_each_triplets(char *line, int *i, int digit_nb, \
		int triplet);
int					check_floor_ceiling_clr_input(char *line);

//cub3d_display
int					display(t_p *p);

//cub3d_display_sprites.c
void			add_sprite(t_cubspr **spr, t_p *p, double yf, double xf);
void			del_if_further(t_p *p, t_cubray *ray, t_cubspr **spr);

//cub3d_display_ray_wall_hgt.c
void			first_h_intersection(t_cubray *ray);
void            first_v_intersection(t_cubray *ray);
void			find_next_xy_h(t_cubray *ray, double xa, double ya);
void			find_next_xy_v(t_cubray *ray, double xa, double ya);
int				check_h_wall(t_cub3d *cub, t_cubray *ray, t_p *p);
int				check_v_wall(t_cub3d *cub, t_cubray *ray, t_p *p);

//cub3d_display_raycasting.c
void			raycasting(t_cub3d *cub, t_cubimg *img, t_cubray *ray, t_p *p);

//movements.c
void			move_front_back(int keycode, t_cub3d *cub);
void			move_left(t_cub3d *cub);
void			move_right(t_cub3d *cub);
void			rotation(int keycode, t_cub3d *cub);

//error_handling.c
void			error(int e_type, t_p *p);
void			error_0(int e_type);
void			error_1(int e_type);
void			error_2(int e_type);
void			free_memory(t_p *p, int e_type);


#endif
