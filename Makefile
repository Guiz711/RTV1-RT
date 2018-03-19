# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 14:03:15 by jgourdin          #+#    #+#              #
#    Updated: 2018/03/19 16:17:24 by hbouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

# For linux, write LINUX
# For mac, write MACOS
OS = MACOS

ifeq ($(OS),LINUX)
INC_FLAGS = -I./includes/linux -I./libft/includes -I./includes/libxml \
			-I./includes
LIB_FLAGS = -L./libft
LIBS = -lft -lmlx -lXext -lX11 -lm -lxml2 -lpthread
else
INC_FLAGS = -I./includes/osx -I./libft/includes -I./includes/libxml \
			-I./includes -I./minilibx_macos
LIB_FLAGS = -L./libft -L./minilibx_macos
LIBS = -lft -lmlx -lm -framework OpenGL -framework Appkit \
		-lxml2
		# `~/.brew/Cellar/libxml2/2.9.7/bin/xml2-config --cflags --libs`
endif


CC = clang

CFLAGS = -Wall -Wextra -Werror #-flto -O3 -march=native

SRC_PATH = src

SRC_NAME = main.c init_rays.c obj_list.c intersection_1.c intersection_2.c \
			trace_ray_1.c trace_ray_2.c utility.c\
			render_modes.c normal.c normal_2.c shader.c threading.c events.c quit.c \
			hook.c reflection_refraction.c antialiasing.c \
			filtre.c loading_screen.c screenshot.c noise_1.c noise_2.c \
			noise_3.c plane_texture_mapping.c texture.c procedural_bump.c \
			procedural_textures_1.c procedural_textures_2.c set_aliasing.c \
			set_aliasing2.c init.c init_texture.c init2.c filtre2.c \
			trans_hook.c rot_hook.c hook2.c scale_utilitary_1.c \
			trans_utilitary_1.c rot_utilitary_1.c rot_utilitary_2.c \
			scale_utilitary_2.c trans_utilitary_2.c

SRC_VEC_PATH = vectors

SRC_VEC_NAME = vec_init.c vec_add.c vec_rev.c vec_sub.c vec_op_1.c vec_op_2.c \
				matrices.c matrices_calc.c matrices_op.c quaternions.c \
				quaternions_op.c

VECTORS = $(addprefix $(SRC_VEC_PATH)/,$(SRC_VEC_NAME))

SRC_NAME += $(VECTORS)

SRC_PARSER_PATH = xml

SRC_PARSER_NAME = xml_check.c xml_lights.c xml_parser.c xml_camera.c xml_errors.c \
				xml_objects.c xml_tools.c xml_tools2.c xml_material.c xml_transform.c \
				xml_tools3.c xml_objects2.c

PARSER = $(addprefix $(SRC_PARSER_PATH)/,$(SRC_PARSER_NAME))

SRC_NAME += $(PARSER)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = obj

OBJ_NAME = $(SRC:.c=.o)

OBJ_VEC = $(subst $(SRC_VEC_PATH)/,,$(OBJ_NAME))
OBJ_PARSER = $(subst $(SRC_PARSER_PATH)/,,$(OBJ_VEC))
OBJ = $(subst $(SRC_PATH),$(OBJ_PATH),$(OBJ_PARSER))

GREEN = \033[32m

all: $(NAME)

$(NAME): compilation_end
ifeq ($(OS), MACOS)
	@make -C ./minilibx_macos --no-print-directory
endif
	@make -C ./libft --no-print-directory
	@$(CC) $(OBJ) -o $@ $(LIB_FLAGS) $(LIBS)
	@echo "$(GREEN)[$(NAME)] Compilation success"

compilation_end: $(OBJ_NAME)
	@echo "$(GREEN)[$(NAME)] .o created"

%.o: %.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ -c $<
	@mv $@ $(OBJ_PATH)

clean:
	@/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@make -C ./libft clean --no-print-directory
	@echo "$(GREEN)[$(NAME)] .o files deleted"
ifeq ($(OS), MACOS)
	@make -C ./minilibx_macos clean --no-print-directory
endif

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean --no-print-directory
	@echo  "$(GREEN)[$(NAME)] executable file deleted"
ifeq ($(OS), MACOS)
	@/bin/rm -f ./minilibx_macos/libmlx.a
endif

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
