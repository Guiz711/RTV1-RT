/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utilitary_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:20:30 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 16:20:31 by hbouchet         ###   ########.fr       */
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

void			scale_triangle(t_args *args)
{
	t_triangle		*tri;
	t_mtx4			w2t;
	t_mtx4			t2w;
	t_mtx4			scl;

	tri = (t_triangle*)args->scene->objs->content;
	scl = args->env->hook.scale == 1 ? scale(1.1, 1.1, 1.1)
		: scale(0.9, 0.9, 0.9);
	w2t = world_to_triangle_mtx(tri);
	t2w = triangle_to_world_mtx(tri);
	tri->p1 = new_coord(tri->p1, w2t);
	tri->p2 = new_coord(tri->p2, w2t);
	tri->p3 = new_coord(tri->p3, w2t);
	tri->p1 = new_coord(tri->p1, scl);
	tri->p2 = new_coord(tri->p2, scl);
	tri->p3 = new_coord(tri->p3, scl);
	tri->p1 = new_coord(tri->p1, t2w);
	tri->p2 = new_coord(tri->p2, t2w);
	tri->p3 = new_coord(tri->p3, t2w);
	args->scene->objs->content = tri;
}
