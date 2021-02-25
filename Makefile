# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonnel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 16:11:01 by abonnel           #+#    #+#              #
#    Updated: 2021/02/24 08:48:46 by abonnel          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	= cub3d.c cub3d_utils.c cub3d_utils_spr.c \
			  cub3d_parsing.c cub3d_parsing_errors.c cub3d_parsing_map.c \
			  cub3d_parsing_closed_map.c \
			  cub3d_display.c cub3d_display_raycasting.c \
			  cub3d_display_ray_wall_hgt.c cub3d_movements.c \
			  cub3d_error_handling.c cub3d_display_sprites.c \
			  cub3d_display_raycasting_utils.c cub3d_parsing_utils.c \
			  cub3d_display_sprites_math.c cub3d_display_utils.c \
			  cub3d_utils_main.c cub3d_save.c cub3d_bonus.c

SRCSPATH= srcs/

OBJS_FILES = $(SRCS_FILES:.c=.o)

OBJSPATH= objs/

SRCS = $(addprefix $(SRCSPATH),$(SRCS_FILES))

OBJS = $(addprefix $(OBJSPATH),$(OBJS_FILES))

NAME	= cub3D

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

$(OBJSPATH)%.o:		$(SRCSPATH)%.c
			$(CC) $(CFLAGS) -c $< -o $@ -I minilibx_mms_20200219/ -I libft_gnl_git/ -I.

$(NAME):	previous $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -L. -lmlx -Llibft_gnl_git -lft -g -o $(NAME)

previous:
			mkdir -p $(OBJSPATH)
			$(MAKE) -C ./libft_gnl_git
			$(MAKE) -C ./minilibx_mms_20200219
			cp minilibx_mms_20200219/libmlx.dylib .

all:		$(NAME)

clean:
			$(RM) $(OBJSPATH)
			$(MAKE) clean -C ./libft_gnl_git

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C ./libft_gnl_git
			$(RM) libmlx.dylib

re:			fclean all

.PHONY:		all clean fclean re
