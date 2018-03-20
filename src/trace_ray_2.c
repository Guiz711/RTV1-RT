/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:36:28 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 14:47:14 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		get_primary_color(t_args *args, t_ray *ray, t_inter *inter)
{
	t_color	color_comp;
	t_vec3	prim_color;
	double	len;

	color_comp.amb_ratio = init_vec3(0, 0, 0);
	color_comp.diff_ratio = init_vec3(0, 0, 0);
	color_comp.spec_ratio = init_vec3(0, 0, 0);
	prim_color = init_vec3(0, 0, 0);
	args->rdr_fct[args->scene->render_mode](args, ray, inter, &color_comp);
	prim_color = add_vec3(color_comp.diff_ratio, color_comp.amb_ratio);
	if (ray->inside)
	{
		len = norm_vec4(sub_vec4(inter->p, ray->orig));
		prim_color = mult_vec3(prim_color,
			init_vec3(exp(-inter->obj->material.absorb.x * len),
			exp(-inter->obj->material.absorb.y * len),
			exp(-inter->obj->material.absorb.z * len)));
	}
	if (inter->obj->content_type == PLANE
		&& inter->obj->material.texture < WALL)
		prim_color = dmult_vec3(prim_color,
			plane_procedural_texture(args, inter));
	prim_color = dmult_vec3(prim_color, inter->obj->material.opacity);
	prim_color = add_vec3(prim_color, color_comp.spec_ratio);
	return (prim_color);
}

t_vec3		get_final_color(t_args *args, t_ray *ray, t_inter *inter, int depth)
{
	t_vec3	prim_color;
	t_vec3	refl_color;
	t_vec3	refr_color;
	double	refl_ratio;

	refl_color = init_vec3(0, 0, 0);
	refr_color = init_vec3(0, 0, 0);
	inter->normal = args->norm_fct[inter->obj->content_type](ray, inter);
	if (inter->obj->content_type == PLANE
		&& inter->obj->material.bump_text != NO_BUMP)
		plane_bump_mapping(args, inter);
	refl_ratio = inter->obj->material.reflect;
	prim_color = get_primary_color(args, ray, inter);
	if (double_not_null(refl_ratio))
		refl_color = dmult_vec3(recursive_ray(args,
			reflected_ray(ray->dir, inter), depth + 1), refl_ratio);
	if (double_not_null(1 - inter->obj->material.opacity))
		refr_color = recursive_ray(args, refracted_ray(ray->dir, inter),
			depth + 1);
	refr_color = dmult_vec3(refr_color,
			(1 - refl_ratio) * (1 - inter->obj->material.opacity));
	prim_color = dmult_vec3(prim_color,
		inter->obj->material.opacity - refl_ratio);
	return (add_vec3(prim_color, add_vec3(refr_color, refl_color)));
}

t_vec3		recursive_ray(t_args *args, t_ray ray, int depth)
{
	t_inter	inter;
	t_vec3	final_color;

	final_color = init_vec3(0, 0, 0);
	if (depth > REFLEXION_DEPTH)
		return (final_color);
	inter = trace_ray(ray, args->scene->objs, args->obj_fct, 0);
	if (inter.obj)
		final_color = get_final_color(args, &ray, &inter, depth);
	return (final_color);
}
