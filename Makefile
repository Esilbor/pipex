# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/22 15:28:31 by bbresil           #+#    #+#              #
#    Updated: 2023/09/01 10:07:13 by bbresil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# project
NAME = pipex
NAME_B = pipex_bonus

# compiler
CC = cc
CFLAGS = -Werror -Wextra -Werror -g3

# libft
LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

# include
INC_LIB = -I./libft/
INC = -I./include/

C_FILES = ./ft_printf/ft_printf.c \
./ft_printf/ft_printf_utils.c \
./gnl/get_next_line.c \
./gnl/get_next_line_utils.c \
./mandatory/pipex.c \
./mandatory/pipex_utils.c \
./mandatory/pipex_utils2.c \
./mandatory/pipex_init.c \
./mandatory/pipex_exec.c \

SRC_B = ./bonus/pipex_bonus.c \
./bonus/pipex_exec_bonus.c \
./bonus/pipex_init_bonus.c \
./bonus/pipex_utils_bonus.c \
./bonus/pipex_utils2_bonus.c \
./bonus/pipex_open_bonus.c \

SRC = $(C_FILES)

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT) :
	@make -sC $(LIBFT_PATH)

%.o : %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(INC_LIB) $(INC)

$(NAME_B) : $(OBJ_B)
	@$(CC) $(CFLAGS) -o $(NAME_B) $(OBJ_B) $(LIBFT) $(INC_LIB) $(INC)


bonus : $(NAME_B)

clean :
	@rm -rf $(OBJ) $(OBJ_B)
	@make clean -sC $(LIBFT_PATH)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)
	@make fclean -sC $(LIBFT_PATH)

re : fclean all

rebonus : fclean re bonus

.PHONY: re clean fclean all rebonus bonus
