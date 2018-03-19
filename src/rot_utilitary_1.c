/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_utilitary_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:22:10 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 16:22:10 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			rot_cone(t_args *args, t_vec3 trans_rot)
{
	t_cone		*cone;

	cone = (t_cone*)args->scene->objs->content;
	cone->dir = new_coord(cone->dir, quat_to_mtx(euler_to_quat(trans_rot)));
	args->scene->objs->content = cone;
}

void			rot_cylinder(t_args *args, t_vec3 trans_rot)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder*)args->scene->objs->content;
	cyl->dir = new_coord(cyl->dir, quat_to_mtx(euler_to_quat(trans_rot)));
	args->scene->objs->content = cyl;
}

void			rot_parab(t_args *args, t_vec3 trans_rot)
{
	t_parab		*parab;

	parab = (t_parab*)args->scene->objs->content;
	parab->dir = new_coord(parab->dir, quat_to_mtx(euler_to_quat(trans_rot)));
	args->scene->objs->content = parab;
}

void			rot_plane(t_args *args, t_vec3 trans_rot)
{
	t_plane		*plane;

	plane = (t_plane*)args->scene->objs->content;
	plane->normal = new_coord(plane->normal,
			quat_to_mtx(euler_to_quat(trans_rot)));
	args->scene->objs->content = plane;
}
