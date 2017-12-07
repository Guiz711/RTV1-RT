/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/07 21:04:01 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <errno.h>
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "libft.h"
# include <stdio.h>
# include <stdint.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

/*
**	Properties
*/

# define WIN_WIDTH 1300
# define WIN_HEIGHT 660
# define FOVX 45
# define COLOR_DEPTH 32
# define ENDIAN 1
# define BUFF_SIZE 4096

# define EXTENSION_NAME ".scn"

# define RAD(x) (M_PI * (x) / 180)

/*
**	Error handling
*/

typedef enum	e_err
{
	NO_ERR,
	ERR_ARGS,
	ERR_INIT_MLX,
	ERR_INIT_WIN,
	ERR_INIT_TEXTURES,
	ERR_MAP,
	ERR_NAME,
	ERR_FILE_EXTENSION,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_READ,
	ERR_FILE_EMPTY,
	ERR_PARSING,
}				t_err;

typedef enum	e_obj_type
{
	NONE,
	CAMERA,
	SPHERE,
	CYLINDER,
	CONE,
	PLAN,
}				t_obj_type;

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_vec4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vec4;

typedef struct	s_mtx4
{
	double		a[4];
	double		b[4];
	double		c[4];
	double		d[4];
}				t_mtx4;

typedef	struct	s_ray
{
	t_vec4		orig;
	t_vec4		dir;
}				t_ray;

typedef struct	s_sphere
{
	t_vec4		center;
	double		radius;
	uint32_t	color;
}				t_sphere;

typedef struct	s_plane
{
	t_vec4		p;
	t_vec4		normal;
	uint32_t	color;
}				t_plane;

typedef struct	s_cone
{
	t_vec4		summit;
	t_vec4		dir;
	double		angle;
	uint32_t	color;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec4		p;
	t_vec4		dir;
	double		radius;
	uint32_t	color;
}				t_cylinder;

typedef	struct		s_obj_lst
{
	t_obj_type		content_type;
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_obj_lst;

typedef struct	s_obj
{
	t_obj_type	type;
	void		*data;
}				t_obj;

typedef struct	s_view
{
	t_vec4		orig;
	t_vec4		orient;
}				t_view;

typedef struct	s_scene
{
	t_view		cam;
	t_list		*items;
}				t_scene;

typedef struct	s_img
{
	void		*ptr;
	int			color_depth;
	int			width;
	int			height;
	int			endian;
	char		*data;
}				t_img;

typedef struct	s_env
{
	void		*init;
	void		*win;
	t_img		*img;
}				t_env;

typedef struct	s_args
{
	t_env		*env;
	t_view		*view;
	t_img		*display;
	t_ray		*ray_buf;
}				t_args;

typedef struct	s_error
{
	int			type;
	char		*detail;
}				t_error;

typedef struct	s_props
{
	char		**cam;
	char		**sph;
}				t_props;

t_ray	*create_ray_array(t_mtx4 v2w);
t_vec4	ft_normalize(t_vec4 v);
double	ft_dot_product(t_vec4 u, t_vec4 v);
t_vec4	new_coord(t_vec4 p, t_mtx4 mtx);
t_mtx4	ft_mtx_mult(t_mtx4 m1, t_mtx4 m2);
t_mtx4	ft_translate(float t_x, float t_y, float t_z);
t_mtx4	ft_rotation(char axis, float pitch);
void	error(t_err err);
int		error_message(const char *message, size_t line);
t_vec4	ft_init_vec4(float x, float y, float z, float w);

/*
**	Quit and initialize functions
*/

/*
**	Events functions
*/

/*
**	Map handling functions
*/

/*
**	Ray casting functions
*/

/*
**	Mlx image handling functions
*/

/*
**	Utility functions
*/

#endif
