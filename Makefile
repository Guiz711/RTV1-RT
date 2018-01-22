# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2018/01/22 04:33:17 by jgourdin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

OS = WIN

ifeq ($(OS),LINUX)
	INC_FLAGS = -I./includes/linux -I./libft/includes
	INC_PATH = includes/linux
	#LIBS = -lft -lmlx -lXext -lX11 -lm
	LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit `~/.brew/Cellar/libxml2/2.9.7/bin/xml2-config --cflags --libs`
else
	INC_FLAGS = -I./includes/osx -I./libft/includes
	INC_PATH = includes/osx
	LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit `~/.brew/Cellar/libxml2/2.9.7/bin/xml2-config --cflags --libs`

endif

LIB_FLAGS = -L./libft

CC = clang

CFLAGS = -Wall -Wextra -Werror

INC_NAME = rtv1.h vectors.h inputs_linux.h X.h xml_parser.h

SRC_PATH = src

SRC_NAME = main.c vec_init.c init_rays.c vec_op.c matrices_calc.c matrices.c mtx_op.c \
			error.c obj_list.c intersection.c trace_ray.c normal.c vec_add.c vec_rev.c \
			vec_sub.c shader.c

PARSER_PATH = xml

PARSER_NAME = xml_check.c xml_lights.c xml_parser.c xml_camera.c xml_errors.c xml_objects.c xml_tools.c xml_tools2.c

PARSER = $(addprefix $(PARSER_PATH)/, $(PARSER_NAME))

SRC_NAME += $(PARSER)

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

#OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJ_NAME = $(SRC:.c=.o)
INC = $(addprefix $(INC_PATH)/,$(INC_NAME))
OBJS = obj/*.o
GREEN = \033[32m

all: $(NAME)

$(NAME): $(OBJ_NAME)
	#make -C ./mlxext
	make -C ./minilibx_macos
	@make -C ./libft --no-print-directory
	@$(CC) $(OBJS) -o $@ $(LIB_FLAGS) $(LIBS)
	@echo "$(GREEN)[$(NAME)] Compilation success"

%.o: %.c $(INC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<
	@mv $@ $(OBJ_PATH)

clean:
	@echo "$(OBJ)"
	@/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@make -C ./libft clean --no-print-directory
	@echo "$(GREEN)[$(NAME)] .o files deleted"
	#make -C ./mlxext clean
	make -C ./minilibx_macos clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean --no-print-directory
	@echo  "$(GREEN)[$(NAME)] executable file deleted"
	#/bin/rm -f ./mlxext/libmlxext.a
	/bin/rm -f ./minilibx_macos/libmlx.a

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
