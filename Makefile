# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 21:17:38 by akostrik          #+#    #+#              #
#    Updated: 2023/07/20 22:15:14 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c calc_image.c utils.c
OBJS = $(addprefix ./.build/, $(SRCS))
OBJS := $(OBJS:%.c=%.o)

all : fdf

fdf	: ${OBJS}
	cc -g $(OBJS) -o fdf -Llibft -lft -Lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

./.build/%.o : ./src/%.c ./libft/libft.a ./mlx/libmlx_Linux.a
	mkdir -p ./.build
	cc -Wall -Werror -Wextra -I ./src -I ./libft -I ./mlx -O3 -c $< -o $@

./libft/libft.a:
	make -C ./libft

clean :
	make -C ./libft clean
	rm -rf ${OBJS}

fclean : clean
	rm -rf fdf ./libft/libft.a

re : fclean all

.PHONY : all clean fclean re
