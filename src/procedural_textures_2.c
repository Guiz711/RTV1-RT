/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:34:34 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/18 14:50:02 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	fractal_sum_perlin(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	size_t	depth;
	double	sum;
	double	div;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		RAD(mat->text_angle)));
	obj_coords = new_coord(obj_coords, rotation);
	sum = 0;
	div = 1;
	depth = 0;
	obj_coords = dmult_vec4(obj_coords, mat->text_scale);
	while (depth < 5)
	{
		sum += eval_coord(mat, obj_coords) * div;
		obj_coords = dmult_vec4(obj_coords, 2);
		div *= 0.5;
		++depth;
	}
	sum = (sum + 1) * 0.5;
	return (sum);
}

double	sinus_sum_perlin(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	size_t	depth;
	double	sum;
	double	div;
	double	x;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		RAD(mat->text_angle)));
	obj_coords = new_coord(obj_coords, rotation);
	x = obj_coords.x;
	sum = 0;
	div = 1;
	depth = 0;
	obj_coords = dmult_vec4(obj_coords, 0.02);
	while (depth < 5)
	{
		sum += eval_coord(mat, obj_coords) * div;
		obj_coords = dmult_vec4(obj_coords, 1.8);
		div *= 0.35;
		++depth;
	}
	sum = (sin((x + sum * 100.0) * 2.0 * M_PI * mat->text_scale) + 1.0) * 0.5;
	return (sum);
}
