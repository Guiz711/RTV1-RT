# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2017/11/14 11:19:30 by gmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

OS = LINUX

ifeq ($(OS),LINUX)
	INC_FLAGS = -I./includes/linux -I./libft/includes
	INC_PATH = includes/linux
	LIBS = -lft -lmlx -lXext -lX11 -lm
	#LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit
else
	INC_FLAGS = -I./includes/osx -I./libft/includes
	INC_PATH = includes/osx
	LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit
endif

SRC_PATH = src

SRC_NAME = main.c parser.c init_rays.c vec_op.c matrices_calc.c matrices.c mtx_op.c \
			error.c

INC_NAME = rtv1.h inputs_linux.h X.h

OBJ_PATH = obj

LIB_FLAGS = -L./libft

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INC = $(addprefix $(INC_PATH)/,$(INC_NAME))

GREEN = \033[32m

all: $(NAME)

$(NAME): $(OBJ)
#	make -C ./mlxext
#	make -C ./minilibx_macos
	@make -C ./libft --no-print-directory
	@$(CC) $(OBJ) -o $@ $(LIB_FLAGS) $(LIBS)
	@echo "$(GREEN)[$(NAME)] Compilation success"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@make -C ./libft clean --no-print-directory
	@echo "$(GREEN)[$(NAME)] .o files deleted"
#	make -C ./mlxext clean
#	make -C ./minilibx_macos clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean --no-print-directory
	@echo  "$(GREEN)[$(NAME)] executable file deleted"
#	/bin/rm -f ./mlxext/libmlxext.a
#	/bin/rm -f ./minilibx_macos/libmlx.a

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
