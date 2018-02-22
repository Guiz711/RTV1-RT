/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:02:24 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/22 15:38:05 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		shadow_attenuation_calc(t_mat *mat, t_inter *inter)
{
	if (!double_not_null(1 - mat->opacity))
		inter->shad_atten = 1;
	else
		inter->shad_atten += mat->opacity;
}

t_inter		trace_ray(t_ray ray, t_obj_lst *objs, t_inter_fct *obj_fct, int shad)
{
	t_inter	inter;
	double	tmp_dist;

	inter.dist = ray.range;
	inter.obj = NULL;
	inter.p = init_vec4(0, 0, 0, 1);
	inter.shad_atten = 0;
	while (objs)
	{
		tmp_dist = obj_fct[objs->content_type](ray, objs->content);
		if (shad && tmp_dist < ray.range && tmp_dist > 0)
		{
			inter.dist = tmp_dist;
			inter.obj = objs;
			shadow_attenuation_calc(&inter.obj->material, &inter);
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
		prim_color = mult_vec3(prim_color, init_vec3(exp(-inter->obj->material.absorb.x * len),
			exp(-inter->obj->material.absorb.y * len), exp(-inter->obj->material.absorb.z * len)));
	}
	if (inter->obj->content_type == PLANE && inter->obj->material.texture != NO_TEXT)
		prim_color = dmult_vec3(prim_color, plane_texture(args, inter));
	prim_color = dmult_vec3(prim_color, inter->obj->material.opacity);
	prim_color = add_vec3(prim_color, color_comp.spec_ratio);
	return (prim_color);
}

double		get_refl_ratio(t_inter *inter, t_ray *ray)
{
	double	refl_ratio;

	refl_ratio = fresnel_calc(inter->normal, ray->dir, 1,
			inter->obj->material.refract);
	refl_ratio = inter->obj->material.reflect
		+ (1.0 - inter->obj->material.reflect) * refl_ratio;
	return (refl_ratio);
}

t_vec3		get_final_color(t_args *args, t_ray *ray, t_inter *inter, int depth, size_t i)
{
	t_ray	new_ray;
	t_vec3	prim_color;
	t_vec3	refl_color;
	t_vec3	refr_color;
	double	refl_ratio;

	refl_color = init_vec3(0, 0, 0);
	refr_color = init_vec3(0, 0, 0);
	inter->normal = args->norm_fct[inter->obj->content_type](ray, inter);
	if (inter->obj->content_type == PLANE && inter->obj->material.bump_text != NO_BUMP)
		plane_bump_mapping(args, inter);
	// if (inter->obj->material.opacity < 1)
		// refl_ratio = get_refl_ratio(inter, ray);
	// else
		refl_ratio = inter->obj->material.reflect;
	prim_color = get_primary_color(args, ray, inter);
	if (double_not_null(refl_ratio))
	{
		new_ray = reflected_ray(ray->dir, inter);
		refl_color = recursive_ray(args, new_ray, depth + 1, i);
		refl_color = dmult_vec3(refl_color, refl_ratio);
	}
	if (double_not_null(1 - inter->obj->material.opacity))
	{
		new_ray = refracted_ray(ray->dir, inter);
		refr_color = recursive_ray(args, new_ray, depth + 1, i);
	}
	refr_color = dmult_vec3(refr_color,
			(1 - refl_ratio) * (1 - inter->obj->material.opacity));
	return (add_vec3(prim_color, add_vec3(refr_color, refl_color)));
}

t_vec3		recursive_ray(t_args *args, t_ray ray, int depth, size_t i)
{
	t_inter	inter;
	t_vec3	final_color;

	final_color = init_vec3(0, 0, 0);
	if (depth > REFLEXION_DEPTH)
		return (final_color);
	inter = trace_ray(ray, args->scene->objs, args->obj_fct, 0);
	if (inter.obj)
			final_color = get_final_color(args, &ray, &inter, depth, i);
	return (final_color);
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
