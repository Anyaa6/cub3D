# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonnel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:51:14 by abonnel           #+#    #+#              #
#    Updated: 2021/01/15 14:33:11 by abonnel          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS	= get_next_line.c get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= gnl.a

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
