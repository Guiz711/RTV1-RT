/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_bump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:44:20 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/16 10:51:09 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4	sine_wave_bump(double angle, double scale, t_vec4 obj_coords)
{
	t_mtx4	rotation;
	t_mtx4	rotation_inv;
	t_vec4	normal;
	double	ratio;

	normal = init_vec4(0, 0, 1, 0);
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	ratio = (sin(obj_coords.x * 2 * M_PI * scale) + 1) * 0.5;
	rotation_inv = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		RAD(-angle)));
	normal.x = ratio;
	normal = normalize_vec4(normal);
	normal = new_coord(normal, rotation_inv);
	return (normal);
}
