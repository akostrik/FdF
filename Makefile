# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 21:17:38 by akostrik          #+#    #+#              #
#    Updated: 2023/07/23 16:07:21 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c calc_image.c utils1.c utils2.c
OBJS = $(addprefix ./.build/, $(SRCS))
OBJS := $(OBJS:%.c=%.o)

all : fdf

fdf	: ${OBJS}
	cc -Wall -Werror -Wextra -g $(OBJS) -o fdf -Llibft -lft -Lminilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

./.build/%.o : ./src/%.c ./libft/libft.a ./minilibx-linux/libmlx_Linux.a
	mkdir -p ./.build
	cc -Wall -Werror -Wextra -I ./src -I ./libft -I ./minilibx-linux -O3 -c $< -o $@

./libft/libft.a :
	make -C ./libft

./minilibx-linux/libmlx_Linux.a :
	make -C ./minilibx-linux

clean :
	make -C ./libft clean
	make -C ./minilibx-linux clean
	rm -rf ${OBJS}

fclean : clean
	rm -rf fdf ./libft/libft.a ./minilibx-linux/libmlx_Linux.a

re : fclean all

.PHONY : all clean fclean re
