/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/24 17:11:30 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "libft.h"
# include <stdio.h>

/*
**	Properties
*/

# define WIN_HEIGHT 10
# define WIN_WIDTH 20
# define FOVY 60
# define COLOR_DEPTH 32
# define ENDIAN 1

/*
**	Error handling
*/

# define ERR_ARGS 1
# define ERR_INIT_MLX 2
# define ERR_INIT_WIN 3
# define ERR_INIT_TEXTURES 4
# define ERR_MAP 5
# define ERR_NAME 6

# define RAD(x) (M_PI * (x) / 180)

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

typedef struct	s_view
{
	double		fov;
	t_vec2		center;
	double		dist;
	double		a_pitch;
	double		dir;
	t_vec2		pos;
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

typedef struct	s_env
{
	void		*init;
	void		*win;
}				t_env;

typedef struct	s_args
{
	t_env		*env;
	t_view		*view;
	t_img		*display;
	t_ray		*ray_buf;
}				t_args;

t_ray	*create_ray_buffer(t_mtx4 *v2w);
t_vec4	ft_normalize(t_vec4 v);
t_vec4	new_coord(t_vec4 p, t_mtx4 mtx);
t_mtx4		ft_mtx_mult(t_mtx4 m1, t_mtx4 m2);
t_mtx4		ft_translate(float t_x, float t_y, float t_z);
t_mtx4		ft_rotation(char axis, float pitch);

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
