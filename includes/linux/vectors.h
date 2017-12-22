/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:14:06 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/22 12:38:34 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

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

t_vec2			init_vec2(float x, float y);
t_vec3			init_vec3(float x, float y, float z);
t_vec4			init_vec4(float x, float y, float z, float w);

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
float			norm_vec4(t_vec4 v);
t_vec4			cross_vec4(t_vec4 u, t_vec4 v);
double			dot_vec4(t_vec4 u, t_vec4 v);

t_mtx4			ft_mtx_mult(t_mtx4 m1, t_mtx4 m2);
t_mtx4			ft_scale(float pitch_x, float pitch_y, float pitch_z);
t_mtx4			ft_translate(float t_x, float t_y, float t_z);
t_mtx4			ft_rotation(char axis, float pitch);

#endif