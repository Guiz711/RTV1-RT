/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/28 16:49:55 by gmichaud         ###   ########.fr       */
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
# include "vectors.h"
# include <stdio.h>
# include <stdint.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

/*
**	Properties
*/

# define WIN_WIDTH 1920//1250
# define WIN_HEIGHT 1080//660
# define FOVX 90
# define COLOR_DEPTH 32
# define ENDIAN 1
# define BUFF_SIZE 4096

# define EXTENSION_NAME ".scn"

# define RAD(x) (M_PI * (x) / 180)
# define SQUARE(x) ((x) * (x))

/*
**	Error handling
*/

typedef enum		e_err
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
	COUNT_OBJ,
}				t_obj_type;

typedef enum	e_shd
{
	NO_SHD,
	FACING,
	SHADOW,
	LAMBERT,
	PHONG,
	COUNT_SHD,
}				t_shd;

typedef	enum	e_lgt_type
{
	DIRECTIONNAL,
	POINT,
	COUNT_LGT,
}				t_lgt_type;

typedef struct	s_sphere
{
	t_vec4		center;
	double		radius;
}				t_sphere;

typedef struct	s_plane
{
	t_vec4		p;
	t_vec4		normal;
}				t_plane;

typedef struct		s_cone
{
	t_vec4			p;
	t_vec4			dir;
	double			angle;
	double			ang_tan;
}					t_cone;

typedef struct		s_cylinder
{
	t_vec4			p;
	t_vec4			dir;
	double			radius;
}					t_cylinder;

typedef struct		s_light
{
	t_lgt_type		type;
	t_vec4			vec;
	t_vec3			diff_i;
	t_vec3			spec_i;
	float			range;
}					t_light;

typedef struct		s_mat
{
	t_shd			model;
	t_vec3			amb;
	t_vec3			diff;
	t_vec3			spec;
	double			shin;
}					t_mat;

typedef	struct		s_o_lst
{
	t_obj_type		content_type;
	void			*content;
	size_t			content_size;
	t_mat			material;
	struct s_o_lst	*next;
}					t_obj_lst;

typedef	struct	s_ray
{
	t_vec4		orig;
	t_vec4		dir;
}				t_ray;

typedef struct	s_inter
{
	double		dist;
	t_vec4		p;
	t_obj_lst	*obj;
}				t_inter;

typedef struct	s_pixel
{
	t_ray		p_ray;
	t_inter		inter;
	t_vec4		normal;
	t_vec3		col_ratio;
}				t_pixel;

typedef struct	s_view
{
	t_vec4		orig;
	t_vec4		orient;
}				t_view;

typedef struct	s_scene
{
	int			shd[4];
	t_view		cam;
	t_obj_lst	*objs;
	t_list		*light;
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
	int			win_width;
	int			win_height;
	int			fov;
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
typedef t_vec4	(*t_norm_fct)(t_pixel*);
typedef void	(*t_shd_fct)(t_pixel*, t_scene*, t_light*, size_t);

typedef struct	s_args
{
	t_env		*env;
	t_scene		*scene;
	t_pixel		*pix_buf;
	t_norm_fct 	norm_fct[4];
	t_inter_fct	obj_fct[4];
	t_shd_fct	shd_fct[5];
}				t_args;

typedef struct	s_error
{
	int			type;
	char		*detail;
}				t_error;

t_pixel			*create_ray_array(t_env *env, t_mtx4 v2w);
t_vec4	new_coord(t_vec4 p, t_mtx4 mtx);
void	error(t_err err);
int		error_message(const char *message, size_t line);

t_obj_lst	*obj_lstnew(t_obj_type type, void const *content, size_t size);
void		obj_lstadd(t_obj_lst **alst, t_obj_lst *new);
double	cone_intersection(t_ray ray, void *obj);
double	sphere_intersection(t_ray ray, void *obj);
double	plane_intersection(t_ray ray, void *obj);
double	cylinder_intersection(t_ray ray, void *obj);
t_vec4	sphere_normal(t_pixel *pixel);
t_vec4	plane_normal(t_pixel *pixel);
t_vec4	cylinder_normal(t_pixel *pixel);
t_vec4	cone_normal(t_pixel *pixel);
int		manage_shaders(t_args *args);
void	raw_color(t_pixel *pix, t_scene *scn, t_light *lgt, size_t size);
void	facing_ratio(t_pixel *pix, t_scene *scn, t_light *lgt, size_t size);
void	lambert_model(t_pixel *pix, t_scene *scn, t_light *lgt, size_t size);
int			trace_primary_rays(t_args *args);

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
