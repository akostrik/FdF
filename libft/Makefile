# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/03 12:54:42 by akalimol          #+#    #+#              #
#    Updated: 2023/07/23 14:17:26 by akostrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
          ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
          ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
          ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
          ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
          ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
          ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS         = $(addprefix ./.build/, $(SRCS))
OBJS		:= $(OBJS:%.c=%.o)

all : libft.a

libft.a : $(OBJS)
	ar rcs libft.a $(OBJS)

./.build/%.o: ./src/%.c
	mkdir -p ./.build
	cc -Wall -Wextra -Werror -I . -c $< -o $@
 
clean :
	rm -f $(OBJS)

fclean : clean
	rm -f libft.a

re : fclean libft.a

.PHONY:		all clean fclean re bonus
