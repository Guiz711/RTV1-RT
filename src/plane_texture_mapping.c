/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture_mapping.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 11:43:42 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/16 12:28:45 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_mtx4	world_to_plane_mtx(t_plane *plane)
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

static t_mtx4	plane_to_world_mtx(t_plane *plane)
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

double	plane_procedural_texture(t_args *args, t_inter *inter)
{
	t_vec4	obj_coords;
	t_plane	*plane;
	t_mat	*mat;
	double	pattern;

	plane = (t_plane*)inter->obj->content;
	mat = &inter->obj->material;
	obj_coords = new_coord(inter->p, world_to_plane_mtx(plane));
	pattern = args->text_fct[mat->texture](mat, obj_coords);
	return pattern;
}

void	plane_texture(t_args *args, t_inter *inter, t_vec3 *diff)
{
	t_vec4	obj_coords;
	t_plane	*plane;
	t_mat	*mat;

	plane = (t_plane*)inter->obj->content;
	mat = &inter->obj->material;
	if (mat->texture != NO_TEXT)
	{
		obj_coords = new_coord(inter->p, world_to_plane_mtx(plane));
		if (mat->texture == WALL)
			map_texture(&args->textures.wall, mat, obj_coords, diff);
		if (mat->texture == MARBLE)
			map_texture(&args->textures.marble, mat, obj_coords, diff);
	}
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
