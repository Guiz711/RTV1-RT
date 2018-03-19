/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:54:30 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 13:13:29 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <errno.h>
# include "mlx.h"
# include "inputs.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "libft.h"
# include "vectors.h"
# include <stdio.h>
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

# define KEY_DIVIDE 75
# define KEY_MULTIPLY 67
# define FORWARD 126
# define BACK 125
# define UP 78
# define DOWN 69
# define LEFT 123
# define RIGHT 124
# define Q_TRANSX 12
# define W_TRANSY 13
# define E_TRANSZ 14
# define A_TRANSX 0
# define S_TRANSY 1
# define D_TRANSZ 2
# define R_ROTX 15
# define T_ROTY 17
# define Y_ROTZ 16
# define F_ROTX 3
# define G_ROTY 5
# define H_ROTZ 4
# define C_SCALE 8
# define V_SCALE 9
# define KEY_I 34
# define SEL args->env->sel_obj
# define WIN_WIDTH 1400
# define WIN_HEIGHT 700
# define FOVX 90
# define COLOR_DEPTH 32
# define ENDIAN 1
# define BUFF_SIZE 4096

# define THREADS_NUMBER 8

# define REFLEXION_DEPTH 5
# define EXTENSION_NAME ".scn"

# define RAD(x) (M_PI * (x) / 180)
# define SQUARE(x) ((x) * (x))

# define LOADING_SCREEN "./pics/loadingscreen.xpm"

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

typedef enum		e_texture
{
	SINUS,
	SINUS_COSINUS,
	STRIPES,
	CHECKERBOARD,
	WEIGHT_SUM_CHECKERBOARD,
	PERLIN,
	FRACTAL_SUM_PERLIN,
	SINUS_SUM_PERLIN,
	WALL,
	MARBLE,
	NO_TEXT
}					t_texture;

typedef enum		e_bump
{
	B_SINUS,
	NO_BUMP
}					t_bump;

typedef enum		e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	PARABOLOID,
	TRIANGLE,
	COUNT_OBJ,
}					t_obj_type;

typedef enum		e_shd
{
	LAMBERT,
	PHONG,
	COUNT_SHD,
}					t_shd;

typedef	enum		e_lgt_type
{
	DIRECTIONAL,
	POINT,
	COUNT_LGT,
}					t_lgt_type;

typedef struct		s_sphere
{
	t_vec4			center;
	double			radius;
}					t_sphere;

typedef struct		s_plane
{
	t_vec4			p;
	t_vec4			normal;
}					t_plane;

typedef struct		s_cone
{
	t_vec4			p;
	t_vec4			dir;
	double			angle;
	double			ang_tan;
}					t_cone;

typedef struct		s_parab
{
	t_vec4			p;
	t_vec4			dir;
	double			k;
}					t_parab;

typedef struct		s_cylinder
{
	t_vec4			p;
	t_vec4			dir;
	double			radius;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vec4		p1;
	t_vec4		p2;
	t_vec4		p3;
	t_vec4		normal;
}					t_triangle;

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
	int				noise_seed;
	t_vec4			noise_map[256];
	int				permutation[512];
	double			max_noise;
	double			text_angle;
	double			text_scale;
	t_bump			bump_text;
	double			bump_angle;
	double			bump_scale;
	t_vec3			amb;
	t_vec3			diff;
	t_vec3			spec;
	t_vec3			absorb;
	double			refract;
	double			reflect;
	double			shin;
	double			opacity;
}					t_mat;

typedef struct		s_o_lst
{
	unsigned int	id_obj;
	t_obj_type		content_type;
	void			*content;
	size_t			content_size;
	t_mat			material;
	struct s_o_lst	*next;
}					t_obj_lst;

typedef struct		s_ray
{
	t_vec4			orig;
	t_vec4			dir;
	double			range;
	int				inside;
}					t_ray;

typedef struct		s_inter
{
	double			dist;
	double			shad_atten;
	t_vec4			p;
	t_vec4			normal;
	t_obj_lst		*obj;
}					t_inter;

typedef struct		s_color
{
	t_vec3			amb_ratio;
	t_vec3			diff_ratio;
	t_vec3			spec_ratio;
}					t_color;

typedef struct		s_pixel
{
	t_ray			p_ray;
	t_inter			inter;
	t_color			color;
}					t_pixel;

typedef struct		s_view
{
	t_vec4			orig;
	t_vec4			orient;
}					t_view;

typedef struct		s_img
{
	void			*ptr;
	int				color_depth;
	int				width;
	int				height;
	int				endian;
	char			*data;
}					t_img;

typedef struct		s_text_img
{
	t_img			wall;
	t_img			marble;
}					t_text_img;

typedef struct		s_poly2
{
	double			a;
	double			b;
	double			c;
	double			disc;
}					t_poly2;

typedef double		(*t_inter_fct)(t_ray, void*);
typedef t_vec4		(*t_norm_fct)(t_ray*, t_inter*);
typedef double		(*t_text_fct)(t_mat*, t_vec4);
typedef t_vec4		(*t_bump_fct)(double, double, t_vec4);

typedef struct		s_scene
{
	char			*path;
	unsigned int	nb_obj;
	int				shd[5];
	int				render_mode;
	double			refra;
	int				filtre;
	t_view			cam;
	t_obj_lst		*objs;
	t_list			*light;
	t_vec3			amb_i;
}					t_scene;


typedef struct		s_hook
{
	int				up_down;
	int				backforw;
	int				left_right;
	int				scale;
	int				trans_x;
	int				trans_y;
	int				trans_z;
	int				rot_x;
	int				rot_y;
	int				rot_z;
}					t_hook;

typedef struct		s_env
{
	int				thread_number;
	t_hook			hook;
	int				rendertmp;
	unsigned int	moving;
	double			aliasing;
	unsigned int	sel_obj;
	void			*init;
	void			*win;
	int				win_width;
	int				win_height;
	int				fov;
	t_img			*img;
	t_img			*lodscreen;
	t_img			*loadbar;
}					t_env;

typedef struct		s_args
{
	t_env			*env;
	t_scene			*scene;
	t_pixel			*pix_buf;
	t_text_img		textures;
	t_norm_fct		norm_fct[6];
	t_inter_fct		obj_fct[6];
	t_text_fct		text_fct[8];
	void			(*modif_scale[6])(struct s_args*);
	void			(*modif_trans[6])(struct s_args*, t_vec3);
	void			(*modif_rot[6])(struct s_args*, t_vec3);
	t_bump_fct		bump_fct[1];
	void			(*rdr_fct[6])(struct s_args*, t_ray*, t_inter*, t_color*);
	t_vec3			(*spec_fct[1])(t_inter*, t_light*);
}					t_args;

typedef struct		s_error
{
	int				type;
	char			*detail;
}					t_error;

typedef struct		s_thread
{
	t_args			*args;
	t_img			*img;
	size_t			start;
	size_t			end;
}					t_thread;

typedef struct		s_noise
{
	int				start[3];
	int				end[3];
	t_vec3			t;
	t_vec4			grad[8];
	t_vec4			dir[8];
	t_vec4			interpol;
}					t_noise;

int					hook(int keycode, t_args *args);
int					check_hook(t_args *args);
int					init_hook(t_env *env);
int					select_obj(int button, int x, int y, t_args *args);
int					modif_scale_obj(t_args *args);
int					modif_trans_obj(t_args *args);
int					modif_rot_obj(t_args *args);
void				scale_sphere(t_args *args);
void				scale_cone(t_args *args);
void				scale_cylinder(t_args *args);
void				scale_parab(t_args *args);
void				scale_triangle(t_args *args);
void				trans_triangle(t_args *args, t_vec3 trans_pos);
void				trans_sphere(t_args *args, t_vec3 trans_pos);
void				trans_cone(t_args *args, t_vec3 trans_pos);
void				trans_cylinder(t_args *args, t_vec3 trans_pos);
void				trans_parab(t_args *args, t_vec3 trans_pos);
void				trans_plane(t_args *args, t_vec3 trans_pos);
void				rot_sphere(t_args *args, t_vec3 trans_rot);
void				rot_cone(t_args *args, t_vec3 trans_rot);
void				rot_cylinder(t_args *args, t_vec3 trans_rot);
void				rot_parab(t_args *args, t_vec3 trans_rot);
void				rot_plane(t_args *args, t_vec3 trans_rot);
void				rot_triangle(t_args *args, t_vec3 trans_rot);

t_mtx4				get_camera_to_world(t_view *view);
t_pixel				*init_pix_buffer(t_env *env, t_mtx4 v2w);
t_vec4				new_coord(t_vec4 p, t_mtx4 mtx);

t_obj_lst			*obj_lstnew(t_obj_type type,
						void const *content, size_t size);
void				obj_lstadd(t_obj_lst **alst, t_obj_lst *new);

double				resolve_poly2(t_poly2 poly);
t_vec3				diffuse_lambert(t_args *args, t_inter *inter,
						t_light *light);
void				convert_color(t_env *env, size_t pos, t_vec3 pix_col);
double				shadow(t_args *args, t_inter *inter, t_light *light);
int					trace_primary_rays(t_args *args);
t_inter				trace_ray(t_ray ray, t_obj_lst *objs,
						t_inter_fct *obj_fct, int shad);
void				trace_rays_mono(t_args *args);
int					manage_threads(t_args *args);
int					keypress(int keycode, void *args);
int					quit(t_args *args);
t_ray				reflected_ray(t_vec4 ray_dir, t_inter *inter);
int					double_not_null(double d);
void				invert(double *a, double *b);
t_vec3				recursive_ray(t_args *args, t_ray ray, int depth);
double				fresnel_calc(t_vec4 normal, t_vec4 ray_dir,
						double n1, double n2);
t_ray				refracted_ray(t_vec4 ray_dir, t_inter *inter);
t_ray				reflected_ray(t_vec4 ray_dir, t_inter *inter);
void				plane_texture(t_args *args, t_inter *inter, t_vec3 *diff);
double				plane_procedural_texture(t_args *args, t_inter *inter);
double				sine_wave(t_mat *mat, t_vec4 obj_coords);
double				sine_cosine_wave(t_mat *mat, t_vec4 obj_coords);
double				stripes(t_mat *mat, t_vec4 obj_coords);
double				checkerboard(t_mat *mat, t_vec4 obj_coords);
double				weight_sum_checkerboard(t_mat *map, t_vec4 obj_coords);
void				plane_bump_mapping(t_args *args, t_inter *inter);
t_vec4				sine_wave_bump(double angle, double scale,
						t_vec4 obj_coords);
void				redraw(t_args *args);
t_bump				char_to_bump(char *str);
void				aliasing(t_args *args, t_pixel *pix, size_t i, size_t end);
void				antialiasing(t_args *args, t_pixel *pix,
						size_t i, size_t end);
int					set_aliasing(int keycode, t_args *args);
double				multiply_aliasing(t_args *args, double aliasing);
double				divide_aliasing(t_args *args, double aliasing);
size_t				draw_pos_anti(t_args *args, int i, t_pixel *pix,
						size_t nb_ray);
void				draw_pos_alia(t_args *args, t_vec3 pix_col,
						size_t nb_pix, size_t i);

void				filter_selector(t_args *args);
void				bandw_filter(t_img *img);
void				negatif_filter(t_img *img);
void				stereoscopie_filter(t_img *img);
void				sepia_filter(t_img *img);
void				motionblur_filter(t_img *img);
int					cartoon_filter(t_img *img);

void				map_texture(t_img *texture, t_mat *mat,
						t_vec4 obj_coords, t_vec3 *diff);
void				fill_text_map(t_mat *mat);
double				eval_coord(t_mat *mat, t_vec4 coords);
double				map_noise(t_mat *mat, t_vec4 obj_coords);
void				compute_corners(t_vec4 *map, int *perm, t_noise *p);
void				compute_directions(t_noise *p);
double				fractal_sum_perlin(t_mat *mat, t_vec4 obj_coords);
double				sinus_sum_perlin(t_mat *mat, t_vec4 obj_coords);
void				put_pixel(int pos, t_img *img, unsigned int color);

int					init_loadingscreen(t_env *env);
int					init_args(t_args *args, t_env *env,
						t_scene *scene, char *path);
void				init_fct_arr(t_args *args);
int					init_textures(t_args *args);
void				add_texture(t_scene *scene);

void				screenshot(t_img *img);
char				*fill_img(char *tmp, t_img *img, size_t p);

/*
**	Primitive intersection functions
*/

double				cone_intersection(t_ray ray, void *obj);
double				sphere_intersection(t_ray ray, void *obj);
double				plane_intersection(t_ray ray, void *obj);
double				cylinder_intersection(t_ray ray, void *obj);
double				paraboloid_intersection(t_ray ray, void *obj);
double				triangle_intersection(t_ray ray, void *obj);

/*
**	Primitive surface normal functions
*/

t_vec4				sphere_normal(t_ray *ray, t_inter *inter);
t_vec4				plane_normal(t_ray *ray, t_inter *inter);
t_vec4				cylinder_normal(t_ray *ray, t_inter *inter);
t_vec4				cone_normal(t_ray *ray, t_inter *inter);
t_vec4				paraboloid_normal(t_ray *ray, t_inter *inter);
t_vec4  			get_triangle_normal(t_vec4 p1, t_vec4 p2, t_vec4 p3);
t_vec4				triangle_normal(t_ray *ray, t_inter *inter);

/*
**	Render management functions
*/

void				render_mode_0(t_args *args, t_ray *ray, t_inter *inter,
						t_color *color);
void				render_mode_1(t_args *args, t_ray *ray, t_inter *inter,
						t_color *color);
void				render_mode_2(t_args *args, t_ray *ray, t_inter *inter,
						t_color *color);
void				render_mode_3(t_args *args, t_ray *ray, t_inter *inter,
						t_color *color);
void				render_mode_4(t_args *args, t_ray *ray, t_inter *inter,
						t_color *color);

/*
**	Specular Highlight functions
*/

t_vec3				specular_phong(t_inter *inter, t_light *light);

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
