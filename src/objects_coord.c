/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 11:43:42 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/22 09:37:08 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mtx4	world_to_plane_mtx(t_plane *plane)
{
	t_vec4	z_axis;
	t_mtx4	rotation;
	t_mtx4	translation;

	z_axis = init_vec4(0, 0, 1, 0);
	translation = translate(plane->p.x, plane->p.y, plane->p.z);
	rotation = quat_to_mtx(axisangle_to_quat(cross_vec4(z_axis, plane->normal),
		acos(dot_vec4(z_axis, plane->normal))));
	return (mtx4_mult(translation, rotation));
}

t_mtx4	plane_to_world_mtx(t_plane *plane)
{
	t_vec4	z_axis;
	t_mtx4	rotation;
	t_mtx4	translation;

	z_axis = init_vec4(0, 0, 1, 0);
	translation = translate(-plane->p.x, -plane->p.y, -plane->p.z);
	rotation = quat_to_mtx(axisangle_to_quat(cross_vec4(z_axis, plane->normal),
		acos(-dot_vec4(z_axis, plane->normal))));
	return (mtx4_mult(translation, rotation));
}

double	sine_wave(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	return ((sin(obj_coords.x * 2 * M_PI * scale) + 1) * 0.5);
}

double	sine_cosine_wave(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	return ((cos(obj_coords.y * 2 * M_PI * scale)
		* sin(obj_coords.x * 2 * M_PI * scale) + 1) * 0.5);
}

double	stripes(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	modulo;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	modulo = obj_coords.x * scale - floor(obj_coords.x * scale);
	if (modulo < 0.5) 
		return (TRUE);
	else
		return (FALSE);
}

double	checkerboard(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	xmodulo;
	double	ymodulo;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	xmodulo = obj_coords.x * scale - floor(obj_coords.x * scale);
	ymodulo = obj_coords.y * scale - floor(obj_coords.y * scale);
	return ((xmodulo < 0.5) ^ (ymodulo < 0.5));
}

double	weight_sum_checkerboard(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	xmodulo;
	double	ymodulo;
	double	div;
	double	sum;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	div = 1;
	sum = 0;
	while (div < 10)
	{
		xmodulo = obj_coords.x * scale * div - floor(obj_coords.x * scale * div);
		ymodulo = obj_coords.y * scale * div - floor(obj_coords.y * scale * div);
		sum += 1 / pow(2, div) * (double)((xmodulo < 0.5) ^ (ymodulo < 0.5));
		++div;
	}
	return (sum);
}

double	plane_texture(t_args *args, t_inter *inter)
{
	t_vec4	obj_coords;
	t_plane	*plane;
	t_mat	*mat;
	double	scale;
	double	pattern;

	plane = (t_plane*)inter->obj->content;
	mat = &inter->obj->material;
	obj_coords = new_coord(inter->p, world_to_plane_mtx(plane));
	scale = 3;
	pattern = args->text_fct[mat->texture](mat->text_angle, mat->text_scale,
		obj_coords);
	return pattern;
}

t_vec4	sine_wave_bump(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	t_mtx4	rotation_inv;
	t_vec4	normal;
	double	ratio;

	normal = init_vec4(0, 0, 1, 0);
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	ratio = (sin(obj_coords.x * 2 * M_PI * scale) + 1) * 0.5;
	rotation_inv = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(-angle)));
	normal.x = ratio;
	normal = normalize_vec4(normal);
	normal = new_coord(normal, rotation_inv);
	return (normal);
}

void	plane_bump_mapping(t_args *args, t_inter *inter)
{
	t_vec4	obj_coords;
	t_plane	*plane;
	t_mat	*mat;
	double	scale;
	t_vec4	normal_var;

	plane = (t_plane*)inter->obj->content;
	mat = &inter->obj->material;
	obj_coords = new_coord(inter->p, world_to_plane_mtx(plane));
	scale = 3;
	normal_var = sine_wave_bump(mat->bump_angle, mat->bump_scale, obj_coords);
	normal_var = args->bump_fct[mat->bump_text](mat->bump_angle,
		mat->bump_scale, obj_coords);
	normal_var = new_coord(normal_var, plane_to_world_mtx(plane));
	inter->normal = mult_vec4(inter->normal, normal_var);
}