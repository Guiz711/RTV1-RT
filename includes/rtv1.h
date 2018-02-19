/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/19 13:35:44 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <errno.h> // to remove?
# include "mlx.h"
# include "inputs.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h> // to remove?
# include "libft.h"
# include "vectors.h"
# include <stdio.h> // to remove?
# include <stdint.h>
# include <pthread.h>

# define KEY_PRESS_MASK	(1L<<0)  
# define KEY_PRESS 2

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

/*
**	Properties
*/
# define UP 13
# define BACK 1
# define LEFT 0
# define RIGHT 2
# define WIN_WIDTH 1440
# define WIN_HEIGHT 780
# define FOVX 90
# define COLOR_DEPTH 32
# define ENDIAN 1
# define BUFF_SIZE 4096

# define THREADS_NUMBER 8

# define REFLEXION_DEPTH 3
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

typedef enum	e_texture
{
	SINUS,
	NO_TEXT
}				t_texture;

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
	LAMBERT,
	PHONG,
	COUNT_SHD,
}				t_shd;

typedef	enum	e_lgt_type
{
	DIRECTIONAL,
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
	double			range;
	t_vec3			atten;
}					t_light;

typedef struct		s_mat
{
	t_shd			model;
	t_texture		texture;
	double			text_angle;
	double			text_scale;
	t_vec3			amb;
	t_vec3			diff;
	t_vec3			spec;
	double			refract;
	double			reflect;
	double			shin;
	double			opacity;
}					t_mat;

typedef	struct		s_o_lst
{
	unsigned int	id_obj;
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
	double		range;
}				t_ray;

typedef struct	s_inter
{
	double		dist;
	double		shad_atten;
	t_vec4		p;
	t_vec4		normal;
	t_obj_lst	*obj;
}				t_inter;

typedef struct	s_color
{
	t_vec3		amb_ratio;
	t_vec3		diff_ratio;
	t_vec3		spec_ratio;
}				t_color;

typedef struct	s_pixel
{
	t_ray		p_ray;
	t_inter		inter;
	t_color		color;
}				t_pixel;

typedef struct	s_view
{
	t_vec4		orig;
	t_vec4		orient;
}				t_view;

typedef struct	s_img
{
	void		*ptr;
	int			color_depth;
	int			width;
	int			height;
	int			endian;
	char		*data;
}				t_img;

typedef struct	s_poly2
{
	double		a;
	double		b;
	double		c;
	double		disc;
}				t_poly2;

typedef double	(*t_inter_fct)(t_ray, void*);
typedef t_vec4	(*t_norm_fct)(t_ray*, t_inter*);
typedef double	(*t_text_fct)(double, double, t_vec4);

typedef struct	s_scene
{
	unsigned int	nb_obj;
	int			shd[5];
	int			render_mode;
	double		refra;
	t_view		cam;
	t_obj_lst	*objs;
	t_list		*light;
	t_vec3		amb_i;
}				t_scene;

# include "xml_parser.h"

typedef struct	s_env
{
	unsigned int	sel_obj;
	void		*init;
	void		*win;
	int			win_width;
	int			win_height;
	int			fov;
	t_img		*img;
}				t_env;

typedef struct	s_args
{
	t_env		*env;
	t_scene		*scene;
	t_pixel		*pix_buf;
	t_norm_fct 	norm_fct[4];
	t_inter_fct	obj_fct[4];
	t_text_fct	text_fct[2];
	void		(*rdr_fct[6])(struct s_args*, t_ray*, t_inter*, t_color*);
	t_vec3		(*spec_fct[1])(t_inter*, t_light*);
}				t_args;

typedef struct	s_error
{
	int			type;
	char		*detail;
}				t_error;

typedef struct	s_thread
{
	t_args		*args;
	t_img		*img;
	size_t		start;
	size_t		end;
}				t_thread;

int			select_obj(int button, int x, int y, t_args *args);
t_mtx4		get_camera_to_world(t_view *view);
t_pixel		*init_pix_buffer(t_env *env, t_mtx4 v2w);
t_vec4		new_coord(t_vec4 p, t_mtx4 mtx);

t_obj_lst	*obj_lstnew(t_obj_type type, void const *content, size_t size);
void		obj_lstadd(t_obj_lst **alst, t_obj_lst *new);

t_vec3		diffuse_lambert(t_inter *inter, t_light *light);
void		convert_color(t_env *env, size_t pos, t_vec3 pix_col);
double		shadow(t_args *args, t_inter *inter, t_light *light);
int			trace_primary_rays(t_args *args);
t_inter		trace_ray(t_ray ray, t_obj_lst *objs, t_inter_fct *obj_fct, int shad);
int			manage_threads(t_args *args);
int			keypress(int keycode, void *args);
int			move_cam(int keycode, t_args *args);
int			quit(t_args *args);
t_ray		reflected_ray(t_vec4 ray_dir, t_inter *inter);
int			modif_scale_obj(int keycode, t_args *args);
int			double_not_null(double d);
void		invert(double *a, double *b);
t_vec3		recursive_ray(t_args *args, t_ray ray, int depth, size_t i);
double	fresnel_calc(t_vec4 normal, t_vec4 ray_dir, double n1, double n2);
t_ray	refracted_ray(t_vec4 ray_dir, t_inter *inter);
t_ray	reflected_ray(t_vec4 ray_dir, t_inter *inter);
double	plane_texture(t_args *args, t_inter *inter);
double	sine_wave(double angle, double scale, t_vec4 obj_coords);

/*
**	Primitive intersection functions
*/

double		cone_intersection(t_ray ray, void *obj);
double		sphere_intersection(t_ray ray, void *obj);
double		plane_intersection(t_ray ray, void *obj);
double		cylinder_intersection(t_ray ray, void *obj);

/*
**	Primitive surface normal functions
*/

t_vec4		sphere_normal(t_ray *ray, t_inter *inter);
t_vec4		plane_normal(t_ray *ray, t_inter *inter);
t_vec4		cylinder_normal(t_ray *ray, t_inter *inter);
t_vec4		cone_normal(t_ray *ray, t_inter *inter);

/*
**	Render management functions
*/

void	render_mode_0(t_args *args, t_ray *ray, t_inter *inter, t_color *color);
void	render_mode_1(t_args *args, t_ray *ray, t_inter *inter, t_color *color);
void	render_mode_2(t_args *args, t_ray *ray, t_inter *inter, t_color *color);
void	render_mode_3(t_args *args, t_ray *ray, t_inter *inter, t_color *color);
void	render_mode_4(t_args *args, t_ray *ray, t_inter *inter, t_color *color);

/*
**	Specular Highlight functions
*/

t_vec3		specular_phong(t_inter *inter, t_light *light);

/*
**	Quit and initialize functions
*/

/*
**	Events functions
*/

/*
**	Mlx image handling functions
*/

/*
**	Utility functions
*/
#endif
