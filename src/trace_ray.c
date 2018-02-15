/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:02:24 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/15 13:20:40 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_inter		trace_ray(t_ray ray, t_obj_lst *objs, t_inter_fct *obj_fct, int shd)
{
	t_inter	inter;
	double	tmp_dist;

	inter.dist = ray.range;
	inter.obj = NULL;
	inter.p = init_vec4(0, 0, 0, 1);
	while (objs)
	{
		tmp_dist = obj_fct[objs->content_type](ray, objs->content);
		if (tmp_dist < inter.dist && tmp_dist > 0)
		{
			inter.dist = tmp_dist;
			inter.obj = objs;
			if (shd && !objs->material.transparency)
				return (inter);
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
