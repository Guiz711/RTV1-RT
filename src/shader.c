/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:46:04 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/10 19:27:53 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	light_attenuation(t_light *light, double dist)
{
	double	intensity;

	if (dist > light->range)
		return (0);
	intensity = 1 / ((light->atten.x * dist * dist) + (light->atten.y * dist)
		+ light->atten.z);
	return (fmax(0, fmin(1, intensity)));
}

t_vec3	diffuse_lambert(t_pixel *pix, t_light *light)
{
	t_vec4			dir;
	t_vec3			col;
	t_vec3			diff;
	double			ratio;
	double			intensity;

	diff = pix->inter.obj->material.diff;
	if (light->type == DIRECTIONAL)
	{
		dir = rev_vec4(light->vec);
		intensity = 1;
	}
	else
	{
		dir = rev_vec4(sub_vec4(pix->inter.p, light->vec));
		intensity = light_attenuation(light, norm_vec4(dir));
		dir = normalize_vec4(dir);
	}
	ratio = intensity * dot_vec4(pix->inter.normal, dir);
	col.z = fmax(0, diff.z * light->diff_i.z * ratio);
	col.y = fmax(0, diff.y * light->diff_i.y * ratio);
	col.x = fmax(0, diff.x * light->diff_i.x * ratio);
	return (col);
}

int		shadow(t_args *args, t_pixel *pix, t_light *light)
{
	t_ray		light_ray;
	t_obj_lst	*objs;
	t_inter		inter;

	objs = args->scene->objs;
	if (light->type == DIRECTIONAL)
	{
		light_ray.dir = rev_vec4(light->vec);
		light_ray.range = 1e6;
	}
	else
	{
		light_ray.dir = rev_vec4(sub_vec4(pix->inter.p, light->vec));;
		light_ray.range = norm_vec4(light_ray.dir);
		light_ray.dir = normalize_vec4(light_ray.dir);
	}
	light_ray.orig = add_vec4(pix->inter.p,
		dmult_vec4(pix->inter.normal, 0.000007));
	light_ray.orig.w = 1;
	inter = trace_ray(light_ray, args->scene->objs, args->obj_fct, 1);
	if (inter.dist < light_ray.range)
		return (0);
	return (1);
}

t_vec3	specular_phong(t_pixel *pix, t_light *light)
{
	t_vec3	ratio;
	t_vec4	r;
	t_vec4	ldir;
	double	ndotl;

	ldir = normalize_vec4(rev_vec4(sub_vec4(pix->inter.p, light->vec)));
	ndotl = 2 * dot_vec4(pix->inter.normal, ldir);
	r = normalize_vec4(sub_vec4(dmult_vec4(pix->inter.normal, ndotl), ldir));
	ratio.x = light->spec_i.x * pix->inter.obj->material.spec.x *
		(pow(dot_vec4(pix->inter.normal, r), pix->inter.obj->material.shin));
	ratio.y = light->spec_i.y * pix->inter.obj->material.spec.y *
		(pow(dot_vec4(pix->inter.normal, r), pix->inter.obj->material.shin));
	ratio.z = light->spec_i.z * pix->inter.obj->material.spec.z *
		(pow(dot_vec4(pix->inter.normal, r), pix->inter.obj->material.shin));
	return (ratio);
}
