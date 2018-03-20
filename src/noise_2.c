/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:20:39 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 09:16:04 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	lerp(double start, double end, double t)
{
	return (start * (1 - t) + end * t);
}

static float	smooth(const float t)
{
	return (t * t * (3 - 2 * t));
}

static void		interpolate(t_noise *p)
{
	p->interpol.x = lerp(dot_vec4(p->grad[0], p->dir[0]),
		dot_vec4(p->grad[1], p->dir[1]), p->t.x);
	p->interpol.y = lerp(dot_vec4(p->grad[2], p->dir[2]),
		dot_vec4(p->grad[3], p->dir[3]), p->t.x);
	p->interpol.z = lerp(dot_vec4(p->grad[4], p->dir[4]),
		dot_vec4(p->grad[5], p->dir[5]), p->t.x);
	p->interpol.w = lerp(dot_vec4(p->grad[6], p->dir[6]),
		dot_vec4(p->grad[7], p->dir[7]), p->t.x);
}

double			eval_coord(t_mat *mat, t_vec4 coords)
{
	t_noise	p;

	p.start[0] = floor(coords.x);
	p.start[1] = floor(coords.y);
	p.start[2] = floor(coords.z);
	p.t.x = coords.x - p.start[0];
	p.t.y = coords.y - p.start[1];
	p.t.z = coords.z - p.start[2];
	p.start[0] = p.start[0] & 255;
	p.start[1] = p.start[1] & 255;
	p.start[2] = p.start[2] & 255;
	p.end[0] = p.start[0] + 1 & 255;
	p.end[1] = p.start[1] + 1 & 255;
	p.end[2] = p.start[2] + 1 & 255;
	compute_corners(mat->noise_map, mat->permutation, &p);
	compute_directions(&p);
	p.t.x = smooth(p.t.x);
	p.t.y = smooth(p.t.y);
	p.t.z = smooth(p.t.z);
	interpolate(&p);
	return (lerp(lerp(p.interpol.x, p.interpol.y, p.t.y),
		lerp(p.interpol.z, p.interpol.w, p.t.y), p.t.z));
}

double			map_noise(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		rad(mat->text_angle)));
	obj_coords = new_coord(obj_coords, rotation);
	return ((eval_coord(mat,
		dmult_vec4(obj_coords, mat->text_scale)) + 1) * 0.5);
}
