/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:12:13 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/16 22:24:51 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	render_mode_0(t_args *args, t_ray *ray, t_inter *inter, t_color *color)
{
	args = NULL;
	ray = NULL;
	if (inter->obj)
		color->diff_ratio = dmult_vec3(inter->obj->material.amb, 1);
}

void	render_mode_1(t_args *args, t_ray *ray, t_inter *inter, t_color *color)
{
	double	dot;

	args = NULL;
	if (inter->obj)
	{
		dot = fmax(0, -dot_vec4(inter->normal, ray->dir));
		color->diff_ratio = dmult_vec3(inter->obj->material.amb, dot);
	}
}

void	render_mode_2(t_args *args, t_ray *ray, t_inter *inter, t_color *color)
{
	t_list	*light;

	ray = NULL;
	if (inter->obj)
	{
		light = args->scene->light;
		while (light)
		{
			color->diff_ratio = add_vec3(color->diff_ratio,
			diffuse_lambert(inter, (t_light*)light->content));
			light = light->next;
		}
		color->amb_ratio = add_vec3(color->amb_ratio,
			mult_vec3(inter->obj->material.amb, args->scene->amb_i));
	}
}

void	render_mode_3(t_args *args, t_ray *ray, t_inter *inter, t_color *color)
{
	t_list	*light;

	ray = NULL;
	if (inter->obj)
	{
		light = args->scene->light;
		while (light)
		{
			if (shadow(args, inter, (t_light*)light->content))
			{
				color->diff_ratio = add_vec3(color->diff_ratio,
				diffuse_lambert(inter, (t_light*)light->content));
			}
			light = light->next;
		}
		color->amb_ratio = add_vec3(color->amb_ratio,
			mult_vec3(inter->obj->material.amb, args->scene->amb_i));
	}
}

void	render_mode_4(t_args *args, t_ray *ray, t_inter *inter, t_color *color)
{
	t_list	*light;
	double	shad_ratio;

	ray = NULL;
		light = args->scene->light;
		while (light)
		{
			shad_ratio = shadow(args, inter, (t_light*)light->content);
			if (double_not_null(shad_ratio))
			{
				color->diff_ratio = add_vec3(color->diff_ratio,
					dmult_vec3(diffuse_lambert(inter, (t_light*)light->content), shad_ratio));
				if (inter->obj->material.model != LAMBERT)
				{
					color->spec_ratio = add_vec3(color->spec_ratio,
					dmult_vec3(args->spec_fct[inter->obj->material.model - 1](inter,
						(t_light*)light->content), shad_ratio));
				}
			}
			light = light->next;
		}
		color->amb_ratio = add_vec3(color->amb_ratio,
			mult_vec3(inter->obj->material.amb, args->scene->amb_i));
}
