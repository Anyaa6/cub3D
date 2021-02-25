/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:15:30 by abonnel           #+#    #+#             */
/*   Updated: 2021/02/25 14:03:46 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "../minilibx_mms_20200219/mlx.h"
# include "../libft_gnl_git/libft.h"
# include "../libft_gnl_git/gnl/get_next_line.h"

typedef struct	s_save {
	int					file_size;
	int					offset;
	int					dib_size;
	int					planes;
	int					b_per_pixel;
	int					img_size;
}				t_save;

typedef	struct	s_cub3d
{
	void				*mlx_p;
	void				*win_p;
	int					r_wid;
	int					r_hgt;
	char				*no;
	char				*so;
	char				*ea;
	char				*we;
	char				*sp;
	unsigned int		floor;
	char				*fl_s;
	unsigned int		top;
	char				*top_s;
	char				**map;
	int					map_w;
	int					map_h;
	char				dir_start;
	int					xstart;
	int					ystart;
	double				x0;
	double				y0;
	double				dir;
}				t_cub3d;

typedef struct	s_cubimg
{
	int					x;
	int					y;
	void				*p_img;
	int					*img;
	int					bits;
	int					lsize;
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
	void				*p_sk;
	int					*sk_img;
	void				*p_fl;
	int					*fl_img;
	void				*p_hu;
	void				*p_lb;
	int					imgs_h;
	int					imgs_w;
	int					txt_b;
	int					txt_l;
	int					txt_e;
}				t_cubimg;

typedef struct	s_cubray {
	double				x0;
	double				y0;
	double				xv;
	double				yv;
	double				xh;
	double				yh;
	double				x;
	double				y;
	int					v;
	int					h;
	int					x_dir;
	int					y_dir;
	double				fov;
	double				eye_h;
	double				s_dist;
	double				w_dist;
	double				w_hgt;
	int					**txt;
	int					offset;
	int					xtxt;
	int					i;
	double				trash;
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
	int					i0;
	int					y0;
	int					yend;
	double				xspr;
	double				yspr;
	double				dx;
	double				dy;
	double				delta;
	double				cdel;
	double				beta;
	struct s_cubspr		*next;
}				t_cubspr;

typedef struct	s_p {
	t_cub3d				*cub;
	t_cubimg			*img;
	t_cubray			*ray;
	t_cubspr			*spr;
	t_cubspr			*first;
}				t_p;

/*
** cub3d_utils.c
*/

int				skip_space(char *s);
void			display_map(t_cub3d *cub);
void			clean_map(t_cub3d *cub);
double			rad(double degrees);
double			deg(double radians);
void			display_list(t_cubspr *spr, t_p *p);
void			del_list(t_cubspr **spr, t_p *p);

/*
** cub3d_utils_main.c
*/

void			init_cub_img(t_cub3d *cub, t_cubimg *img, t_cubray *ray, \
		t_p *p);
void			init_mlx(t_cub3d *cub);
void			init_img_sprite(t_cub3d *cub, t_cubimg *img, t_p *p);
void			init_imgs(t_cub3d *cub, t_cubimg *img, t_p *p);

/*
** cub3d_save.c
*/

void			save_bmp(t_p *p, char *argv);

/*
** cub3d_bonus.c
*/

void			sky_floor_texture(t_cub3d *cub, char *line);

/*
** cub3d_parsing.c
*/

void			parsing_cub(char *argv1, t_p *p);
void			graphic_specs(t_cub3d *cub, char *line, t_p *p);
void			get_resolution(t_cub3d *cub, char *line, t_p *p);
void			floor_ceiling_color(t_cub3d *cub, char *line, int i, t_p *p);
void			elements_path(t_cub3d *cub, char *line, int i);

/*
** cub3d_map.c
*/

void			get_map(int fd, t_p *p, char *line);
void			find_player_start(t_cub3d *cub, t_p *p);

/*
** cub3d_closed_map.c
*/

void			map_is_closed(t_cub3d *cub, t_p *p);

/*
** cub3d_parsing_errors.c
*/

int				check_res_input(char *line, int size, t_p *p);
void			parsing_error(char *argv1, char *line, t_p *p);
int				check_each_triplets(char *line, int *i, int digit_nb, \
		int triplet);
int				check_floor_ceiling_clr_input(char *line);

/*
** cub3d_display
*/

int				display(t_p *p);

/*
** cub3d_display_utils.c
*/

void			find_next_xy_v(t_cubray *ray, double xa, double ya);
void			find_next_xy_h(t_cubray *ray, double xa, double ya);
void			new_img(t_cub3d *cub, t_cubimg *img, t_p *p);

/*
** cub3d_display_sprites.c
*/

void			add_sprite(t_cubspr **spr, t_p *p, double yf, double xf);
void			del_if_further(t_p *p, t_cubray *ray, t_cubspr **spr);

/*
** cub3d_display_sprites_math.c
*/

void			set_start_stop_spr(t_p *p, t_cubspr *node);
void			mesures_to_sprcenter(t_p *p, t_cubspr *node);
void			xspr_step(t_p *p, t_cubspr *spr);
double			dist_to_center(double yf, double xf, t_p *p);

/*
** cub3d_display_ray_wall_hgt.c
*/

void			first_h_intersection(t_cubray *ray);
void			first_v_intersection(t_cubray *ray);
void			find_next_xy_h(t_cubray *ray, double xa, double ya);
void			find_next_xy_v(t_cubray *ray, double xa, double ya);
int				check_h_wall(t_cub3d *cub, t_cubray *ray, t_p *p);
int				check_v_wall(t_cub3d *cub, t_cubray *ray, t_p *p);

/*
**cub3d_display_raycasting.c
*/

void			raycasting(t_cub3d *cub, t_cubimg *img, t_cubray *ray, t_p *p);

/*
**cub3d_display_raycasting_utils.c
*/

void			set_x_y_direction(t_cubray *ray);
void			init_ray_struct(t_cub3d *cub, t_cubray *ray);
void			set_start_stop(int *stop, double *ytxt, double *step, t_p *p);
void			set_xtxt(t_cubray *ray);

/*
** movements.c
*/

void			move_front_back(int keycode, t_cub3d *cub);
void			move_left(t_cub3d *cub);
void			move_right(t_cub3d *cub);
void			rotation(int keycode, t_cub3d *cub);

/*
**error_handling.c
*/

void			error(int e_type, t_p *p);
void			error_0(int e_type);
void			error_1(int e_type);
void			free_memory(t_p *p);

#endif
