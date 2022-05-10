# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/20 17:28:24 by cjulienn          #+#    #+#              #
#    Updated: 2022/05/06 13:36:08 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= so_long

SRCS= ./srcs/so_long.c \
	  ./srcs/check_map_validity_1.c \
	  ./srcs/check_map_validity_2.c \
	  ./srcs/init_game_1.c \
	  ./srcs/init_game_2.c \
	  ./srcs/utils.c \
	  ./srcs/display_map.c \
	  ./srcs/handle_events.c \
	  ./srcs/player_moves_1.c \
	  ./srcs/player_moves_2.c \
	  ./srcs/init_structs.c

OBJS = $(SRCS:.c=.o)

INCLUDE_PATH = ./includes/

LIBFT_LIB = libft.a
LIBFT_PATH = ./libft/

MINILIBX_PATH= ./mlx_std/

CC= gcc
CFLAGS= -Wall -Wextra -Werror -I$(INCLUDE_PATH) -I$(MINILIBX_PATH)

RM= rm -f

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(MAKE) -C $(MINILIBX_PATH)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -Lmlx_std -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo $(NAME) successfully made !!!

all: 
	$(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MINILIBX_PATH) clean
	$(RM) $(OBJS)
	
fclean:	clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re
