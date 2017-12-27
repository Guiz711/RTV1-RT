/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:02:24 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/27 22:29:49 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_inter		trace_ray(t_ray ray, t_obj_lst *objs, t_inter_fct *obj_fct)
{
	t_inter	inter;
	double	tmp_dist;

	inter.dist = 1e6;
	inter.obj = NULL;
	inter.p = init_vec4(0, 0, 0, 1);
	while (objs)
	{
		tmp_dist = obj_fct[objs->content_type](ray, objs->content);
		if (tmp_dist < inter.dist && tmp_dist > 0)
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

int			trace_primary_rays(t_args *args)
{
	size_t		i;
	size_t		len;
	t_pixel		*pix;

	pix = args->pix_buf;
	len = args->env->win_width * args->env->win_height;
	i = 0;
	while (i < len)
	{
		pix[i].inter = trace_ray(pix[i].p_ray, args->scene->objs,
			args->obj_fct);
		pix[i].normal = args->norm_fct[pix[i].inter.obj->content_type](&pix[i]);
		++i;
	}
	return (0);
}

		/*if (rays[i].inter_obj && rays[i].inter_obj->content_type == SPHERE)
		{
			rays[i].obj_normal = sphere_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_sphere*)rays[i].inter_obj->content)->color;
		}
		else if (rays[i].inter_obj && rays[i].inter_obj->content_type == PLANE)
		{
			rays[i].obj_normal = plane_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_plane*)rays[i].inter_obj->content)->color;
		}
		else if (rays[i].inter_obj && rays[i].inter_obj->content_type == CYLINDER)
		{
			rays[i].obj_normal = cylinder_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_cylinder*)rays[i].inter_obj->content)->color;
		}
		else if (rays[i].inter_obj && rays[i].inter_obj->content_type == CONE)
		{
			rays[i].obj_normal = cone_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_cone*)rays[i].inter_obj->content)->color;
		}*/