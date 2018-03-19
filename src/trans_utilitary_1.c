/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utilitary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:52:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 18:07:30 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			trans_sphere(t_args *args, t_vec3 trans_pos)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)args->scene->objs->content;
	sphere->center = new_coord(sphere->center,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	args->scene->objs->content = sphere;
}

void			trans_cone(t_args *args, t_vec3 trans_pos)
{
	t_cone		*cone;

	cone = (t_cone*)args->scene->objs->content;
	cone->p = new_coord(cone->p,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	args->scene->objs->content = cone;
}

void			trans_cylinder(t_args *args, t_vec3 trans_pos)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder*)args->scene->objs->content;
	cyl->p = new_coord(cyl->p,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	args->scene->objs->content = cyl;
}

void			trans_parab(t_args *args, t_vec3 trans_pos)
{
	t_parab		*parab;

	parab = (t_parab*)args->scene->objs->content;
	parab->p = new_coord(parab->p,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	args->scene->objs->content = parab;
}

void			trans_plane(t_args *args, t_vec3 trans_pos)
{
	t_plane		*plane;

	plane = (t_plane*)args->scene->objs->content;
	plane->p = new_coord(plane->p,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	args->scene->objs->content = plane;
}
