/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:02:24 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/16 12:07:06 by gmichaud         ###   ########.fr       */
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

// int			trace_primary_rays(t_args *args)
// {
// 	size_t		i;
// 	size_t		len;
// 	t_pixel		*pix;
// 	t_vec3		pix_col;

// 	pix = args->pix_buf;
// 	len = args->env->win_width * args->env->win_height;
// 	i = 0;
// 	while (i < len)
// 	{
// 		pix[i].inter = trace_ray(pix[i].p_ray, args->scene->objs,
// 			args->obj_fct, 0);
// 		if (pix[i].inter.obj)
// 			pix[i].inter.normal =
// 				args->norm_fct[pix[i].inter.obj->content_type](&pix[i].p_ray, &pix[i].inter);
// 		args->rdr_fct[args->scene->render_mode](args, &pix[i]);
// 		pix_col = init_vec3(0, 0, 0);
// 		convert_color(args->env, i, pix_col);
// 		++i;
// 	}
// 	return (0);
// }
