/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utilitary_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 12:55:07 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/19 13:10:29 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_mtx4	world_to_triangle_mtx(t_triangle *tri)
{
	t_vec4	z_axis;
	t_vec4	center;
	t_mtx4	translation;

	z_axis = init_vec4(0, 0, 1, 0);
	center.x = (tri->p1.x + tri->p2.x + tri->p3.x) / 3;
	center.y = (tri->p1.y + tri->p2.y + tri->p3.y) / 3;
	center.z = (tri->p1.z + tri->p2.z + tri->p3.z) / 3;
	center.w = 1;
	translation = translate(-center.x, -center.y, -center.z);
	return (translation);
}

static t_mtx4	triangle_to_world_mtx(t_triangle *tri)
{
	t_vec4	z_axis;
	t_vec4	center;
	t_mtx4	translation;

	z_axis = init_vec4(0, 0, 1, 0);
	center.x = (tri->p1.x + tri->p2.x + tri->p3.x) / 3;
	center.y = (tri->p1.y + tri->p2.y + tri->p3.y) / 3;
	center.z = (tri->p1.z + tri->p2.z + tri->p3.z) / 3;
	center.w = 1;
	translation = translate(center.x, center.y, center.z);
	return (translation);
}

void			rot_triangle(t_args *args, t_vec3 trans_rot)
{
	t_triangle		*tri;
	t_mtx4			w2t;
	t_mtx4			t2w;
	t_mtx4			rot;

	tri = (t_triangle*)args->scene->objs->content;
	rot = quat_to_mtx(euler_to_quat(trans_rot));
	w2t = world_to_triangle_mtx(tri);
	t2w = triangle_to_world_mtx(tri);
	tri->p1 = new_coord(tri->p1, w2t);
	tri->p2 = new_coord(tri->p2, w2t);
	tri->p3 = new_coord(tri->p3, w2t);
	tri->p1 = new_coord(tri->p1, rot);
	tri->p2 = new_coord(tri->p2, rot);
	tri->p3 = new_coord(tri->p3, rot);
	tri->p1 = new_coord(tri->p1, t2w);
	tri->p2 = new_coord(tri->p2, t2w);
	tri->p3 = new_coord(tri->p3, t2w);
	tri->normal = new_coord(tri->normal, rot);
	args->scene->objs->content = tri;
}
