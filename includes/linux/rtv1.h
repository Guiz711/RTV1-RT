/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/10 10:12:57 by gmichaud         ###   ########.fr       */
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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define FOVX 60
# define COLOR_DEPTH 32
# define ENDIAN 1
# define BUFF_SIZE 4096

# define EXTENSION_NAME ".scn"

# define RAD(x) (M_PI * (x) / 180)
# define SQUARE(x) ((x) * (x))

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
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
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

typedef struct	s_sphere
{
	t_vec4		center;
	double		radius;
	t_vec3		color;
}				t_sphere;

typedef struct	s_plane
{
	t_vec4		p;
	t_vec4		normal;
	t_vec3		color;
}				t_plane;

typedef struct	s_cone
{
	t_vec4		p;
	t_vec4		dir;
	double		angle;
	double		ang_tan;
	t_vec3		color;
}				t_cone;

typedef struct	s_cylinder
{
	t_vec4		p;
	t_vec4		dir;
	double		radius;
	t_vec3		color;
}				t_cylinder;

typedef struct	s_light
{
	t_vec4		dir;
	float		intensity;
	t_vec3		color;
}				t_light;

typedef	struct		s_obj_lst
{
	t_obj_type		content_type;
	void			*content;
	size_t			content_size;
	struct s_obj_lst	*next;
}					t_obj_lst;

typedef	struct	s_ray
{
	t_vec4		orig;
	t_vec4		dir;
	double		inter_dist;
	t_obj_lst	*inter_obj;
	t_vec4		obj_normal;
	t_vec3		color;	
}				t_ray;

typedef struct	s_view
{
	t_vec4		orig;
	t_vec4		orient;
}				t_view;

typedef struct	s_scene
{
	t_view		cam;
	t_obj_lst	*objs;
	t_light		light;
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

typedef struct	s_poly2
{
	double	a;
	double	b;
	double	c;
	double	disc;
}				t_poly2;

typedef double	(*t_inter_fct)(t_ray, void*);

typedef struct	s_args
{
	t_env		*env;
	t_scene		*scene;
	t_ray		*ray_buf;
	t_inter_fct	obj_fct[4];
}				t_args;

typedef struct	s_error
{
	int			type;
	char		*detail;
}				t_error;

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
t_vec3		ft_init_vec3(float x, float y, float z);

t_obj_lst	*obj_lstnew(t_obj_type type, void const *content, size_t size);
void		obj_lstadd(t_obj_lst **alst, t_obj_lst *new);
double	cone_intersection(t_ray ray, void *obj);
double	sphere_intersection(t_ray ray, void *obj);
double	plane_intersection(t_ray ray, void *obj);
double	cylinder_intersection(t_ray ray, void *obj);
t_vec4	sphere_normal(t_ray ray, void *obj);
t_vec4	plane_normal(t_ray ray, void *obj);
t_vec4	cylinder_normal(t_ray ray, void *obj);
t_vec4	cone_normal(t_ray ray, void *obj);
int		raytracing(t_args *args);

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
