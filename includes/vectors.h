/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:14:06 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/22 09:31:05 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef enum	e_axis
{
	X,
	Y,
	Z,
}				t_axis;

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

/*
** Vector functions
*/

t_vec2			init_vec2(double x, double y);
t_vec3			init_vec3(double x, double y, double z);
t_vec4			init_vec4(double x, double y, double z, double w);
t_vec3			vec4_to_vec3(t_vec4 v);

t_vec2			add_vec2(t_vec2 u, t_vec2 v);
t_vec3			add_vec3(t_vec3 u, t_vec3 v);
t_vec4			add_vec4(t_vec4 u, t_vec4 v);

t_vec2			sub_vec2(t_vec2 u, t_vec2 v);
t_vec3			sub_vec3(t_vec3 u, t_vec3 v);
t_vec4			sub_vec4(t_vec4 u, t_vec4 v);

t_vec2			rev_vec2(t_vec2 u);
t_vec3			rev_vec3(t_vec3 u);
t_vec4			rev_vec4(t_vec4 u);

t_vec4			normalize_vec4(t_vec4 v);
double			norm_vec4(t_vec4 v);
t_vec4			cross_vec3(t_vec3 u, t_vec3 v);
t_vec4			cross_vec4(t_vec4 u, t_vec4 v);
double			dot_vec3(t_vec3 u, t_vec3 v);
double			dot_vec4(t_vec4 u, t_vec4 v);
t_vec3			dmult_vec3(t_vec3 u, double n);
t_vec4			dmult_vec4(t_vec4 u, double n);
t_vec3			mult_vec3(t_vec3 u, t_vec3 v);
t_vec4			mult_vec4(t_vec4 u, t_vec4 v);

/*
** Matrix functions
*/

t_mtx4			identity(void);
t_mtx4			scale(double pitch_x, double pitch_y, double pitch_z);
t_mtx4			translate(double t_x, double t_y, double t_z);
t_mtx4			rotate(t_axis axis, double pitch);
t_mtx4			mtx4_mult(t_mtx4 m1, t_mtx4 m2);
t_vec4			new_coord(t_vec4 p, t_mtx4 mtx);

/*
** Quaternion functions
*/

t_vec4			axisangle_to_quat(t_vec4 axis, double angle);
t_vec4			euler_to_quat(t_vec3 rot);
double			norm_quat(t_vec4 q);
t_vec4			normalize_quat(t_vec4 q);
t_vec4			mult_quat(t_vec4 q1, t_vec4 q2);
t_mtx4			quat_to_mtx(t_vec4	q);

#endif
