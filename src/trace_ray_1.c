/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:35:54 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 19:44:08 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	shadow_attenuation_calc(t_mat *mat, t_inter *inter, double dist)
{
	inter->dist = dist;
	if (!double_not_null(1 - mat->opacity))
		inter->shad_atten = 1;
	else
		inter->shad_atten += mat->opacity;
}

static void	init_inter(t_inter *inter, double range)
{
	inter->dist = range;
	inter->obj = NULL;
	inter->p = init_vec4(0, 0, 0, 1);
	inter->shad_atten = 0;
}

t_inter		trace_ray(t_ray ray, t_obj_lst *objs, t_inter_fct *ob_fct, int shad)
{
	t_inter	inter;
	double	tmp_dist;

	init_inter(&inter, ray.range);
	while (objs)
	{
		tmp_dist = ob_fct[objs->content_type](ray, objs->content);
		if (shad && tmp_dist < ray.range && tmp_dist > 0)
		{
			inter.obj = objs;
			shadow_attenuation_calc(&inter.obj->material, &inter, tmp_dist);
			if (inter.shad_atten >= 1.0)
				return (inter);
		}
		else if (!shad && tmp_dist < inter.dist && tmp_dist > 0)
		{
			inter.dist = tmp_dist;
			inter.obj = objs;
		}
		objs = objs->next;
	}
	inter.p = add_vec4(ray.orig, dmult_vec4(ray.dir, inter.dist));
	inter.p.w = 1;
	return (inter);
}
