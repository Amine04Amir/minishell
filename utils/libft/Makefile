# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mobouifr <mobouifr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 16:18:47 by mobouifr          #+#    #+#              #
#    Updated: 2024/09/10 14:19:25 by mobouifr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isspace.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_putendl_fd.c \
	ft_itoa.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_substr.c \
	ft_split.c \
	ft_ssplit.c \
	ft_strtrim.c 
	
	
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
INC = -I../../includes/
all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar -rc $(NAME) $?

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
