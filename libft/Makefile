# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 09:19:42 by bbresil           #+#    #+#              #
#    Updated: 2023/07/14 10:20:27 by bbresil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
ft_toupper.c ft_tolower.c ft_atoi.c ft_strlcat.c ft_memset.c ft_bzero.c \
ft_memcpy.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_strlcpy.c ft_memcmp.c ft_strnstr.c \
ft_memchr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strncmp.c ft_strjoin.c ft_strtrim.c \
ft_itoa.c ft_putchar_fd.c ft_strmapi.c ft_striteri.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_split.c ft_atol.c ft_free_tab.c ft_free_n_tab.c


OBJ = $(SRC:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c

BONUS_OBJ = $(BONUS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus : $(BONUS_OBJ)
	ar rc $(NAME) $(BONUS_OBJ)

clean :
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
