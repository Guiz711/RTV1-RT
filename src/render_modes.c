/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:12:13 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/08 11:14:28 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	render_mode_0(t_args *args, t_pixel *pix, size_t pos)
{
	if (pix->inter.obj)
		pix->diff_ratio = dmult_vec3(pix->inter.obj->material.amb, 1);
	process_color(args->env, pix, pos);
}

void	render_mode_1(t_args *args, t_pixel *pix, size_t pos)
{
	double	dot;

	if (pix->inter.obj)
	{
		dot = fmax(0, -dot_vec4(pix->normal, pix->p_ray.dir));
		pix->diff_ratio = dmult_vec3(pix->inter.obj->material.amb, dot);
	}
	process_color(args->env, pix, pos);
}

void	render_mode_2(t_args *args, t_pixel *pix, size_t pos)
{
	t_list	*light;

	if (pix->inter.obj)
	{
		light = args->scene->light;
		while (light)
		{
			pix->diff_ratio = add_vec3(pix->diff_ratio,
			diffuse_lambert(pix, (t_light*)light->content));
			light = light->next;
		}
		pix->amb_ratio = add_vec3(pix->amb_ratio,
			mult_vec3(pix->inter.obj->material.amb, args->scene->amb_i));
	}
	process_color(args->env, pix, pos);
}

void	render_mode_3(t_args *args, t_pixel *pix, size_t pos)
{
	t_list	*light;

	if (pix->inter.obj)
	{
		light = args->scene->light;
		while (light)
		{
			if (shadow(args, pix, (t_light*)light->content))
			{
				pix->diff_ratio = add_vec3(pix->diff_ratio,
				diffuse_lambert(pix, (t_light*)light->content));
			}
			light = light->next;
		}
		pix->amb_ratio = add_vec3(pix->amb_ratio,
			mult_vec3(pix->inter.obj->material.amb, args->scene->amb_i));
	}
	process_color(args->env, pix, pos);
}

void	render_mode_4(t_args *args, t_pixel *pix, size_t pos)
{
	t_list	*light;

	if (pix->inter.obj)
	{
		light = args->scene->light;
		while (light)
		{
			if (shadow(args, pix, (t_light*)light->content))
			{
				pix->diff_ratio = add_vec3(pix->diff_ratio,
				diffuse_lambert(pix, (t_light*)light->content));
				if (pix->inter.obj->material.model != LAMBERT)
				{
					pix->spec_ratio = add_vec3(pix->spec_ratio,
					args->spec_fct[pix->inter.obj->material.model - 1](pix,
						(t_light*)light->content));
				}
			}
			light = light->next;
		}
		pix->amb_ratio = add_vec3(pix->amb_ratio,
			mult_vec3(pix->inter.obj->material.amb, args->scene->amb_i));
	}
	process_color(args->env, pix, pos);
}
