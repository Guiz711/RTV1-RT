/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:01:19 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 11:54:05 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	map_texture(t_img *texture, t_mat *mat, t_vec4 obj_coords, t_vec3 *diff)
{
	t_mtx4		rotation;
	double		angle;
	int			color;
	int			i;
	int			j;

	angle = mat->text_angle;
	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0),
		RAD(angle)));
	obj_coords = new_coord(obj_coords, rotation);
	i = abs((int)fmodf(obj_coords.x * mat->text_scale, 1024.0));
	j = abs((int)fmodf(obj_coords.y * mat->text_scale, 1024.0));
	color = ((int*)texture->data)[j * 1024 + i];
	diff->x = (double)((color >> 16) & 0xFF) / 255.0;
	diff->y = (double)((color >> 8) & 0xFF) / 255.0;
	diff->z = (double)((color) & 0xFF) / 255.0;
}
