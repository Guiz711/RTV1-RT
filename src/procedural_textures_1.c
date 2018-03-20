/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:22:08 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 09:17:03 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	sine_wave(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	angle;
	double	scale;

	angle = mat->text_angle;
	scale = mat->text_scale;
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		rad(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	return ((sin(obj_coords.x * 2 * M_PI * scale) + 1) * 0.5);
}

double	sine_cosine_wave(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	angle;
	double	scale;

	angle = mat->text_angle;
	scale = mat->text_scale;
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		rad(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	return ((cos(obj_coords.y * 2 * M_PI * scale)
		* sin(obj_coords.x * 2 * M_PI * scale) + 1) * 0.5);
}

double	stripes(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	modulo;
	double	angle;
	double	scale;

	angle = mat->text_angle;
	scale = mat->text_scale;
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		rad(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	modulo = obj_coords.x * scale - floor(obj_coords.x * scale);
	if (modulo < 0.5)
		return (TRUE);
	else
		return (FALSE);
}

double	checkerboard(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	xmodulo;
	double	ymodulo;
	double	angle;
	double	scale;

	angle = mat->text_angle;
	scale = mat->text_scale;
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		rad(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	xmodulo = obj_coords.x * scale - floor(obj_coords.x * scale);
	ymodulo = obj_coords.y * scale - floor(obj_coords.y * scale);
	return ((xmodulo < 0.5) ^ (ymodulo < 0.5));
}

double	weight_sum_checkerboard(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	double	xmodulo;
	double	ymodulo;
	double	div;
	double	sum;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		rad(mat->text_angle)));
	obj_coords = new_coord(obj_coords, rotation);
	div = 1;
	sum = 0;
	while (div < 10)
	{
		xmodulo = obj_coords.x * mat->text_scale * div - floor(obj_coords.x
			* mat->text_scale * div);
		ymodulo = obj_coords.y * mat->text_scale * div - floor(obj_coords.y
			* mat->text_scale * div);
		sum += 1 / pow(2, div) * (double)((xmodulo < 0.5) ^ (ymodulo < 0.5));
		++div;
	}
	return (sum);
}
