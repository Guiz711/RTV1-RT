/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_utilitary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:48:54 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 16:52:36 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			scale_sphere(t_args *args)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)args->scene->objs->content;
	sphere->radius = (args->env->hook.scale == 1 ?
			sphere->radius * 1.1 : sphere->radius / 1.1);
	args->scene->objs->content = sphere;
}

void			scale_cone(t_args *args)
{
	t_cone		*cone;

	cone = (t_cone*)args->scene->objs->content;
	cone->angle =
		(args->env->hook.scale == 1 ? cone->angle * 1.1 : cone->angle / 1.1);
	cone->ang_tan = 1 + square(tan(rad(cone->angle * 0.5)));
	args->scene->objs->content = cone;
}

void			scale_cylinder(t_args *args)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder*)args->scene->objs->content;
	cyl->radius =
		(args->env->hook.scale == 1 ? cyl->radius * 1.1 : cyl->radius / 1.1);
	args->scene->objs->content = cyl;
}

void			scale_parab(t_args *args)
{
	t_parab		*parab;

	parab = (t_parab*)args->scene->objs->content;
	parab->k =
		(args->env->hook.scale == 1 ? parab->k * 1.1 : parab->k / 1.1);
	args->scene->objs->content = parab;
}

int				modif_scale_obj(t_args *args)
{
	t_obj_lst	*tmp;

	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj
			&& args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	if (args->scene->objs->content_type != PLANE)
		args->modif_scale[args->scene->objs->content_type](args);
	args->scene->objs = tmp;
	return (0);
}
