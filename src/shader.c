/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:46:04 by gmichaud          #+#    #+#             */
/*   Updated: 2018/01/29 10:38:09 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(int pos, t_img *img, unsigned int color)
{
	char	*data;
	int		width;
	int		inc;

	data = img->data;
	inc = img->color_depth / 8;
	width = img->width; //* (COLOR_DEPTH / 8);
	ft_memcpy(&data[pos * inc], &color, sizeof(color));
}

void	process_color(t_env *env, t_pixel *pix, size_t pos)
{
	t_vec3		ratio;
	uint32_t	hex_col;
	unsigned	char *comp;

	ratio.x = pix->amb_ratio.x + pix->diff_ratio.x + pix->spec_ratio.x;
	ratio.y = pix->amb_ratio.y + pix->diff_ratio.y + pix->spec_ratio.y;
	ratio.z = pix->amb_ratio.z + pix->diff_ratio.z + pix->spec_ratio.z;
	hex_col = 0;
	comp = (unsigned char*)&hex_col;
	comp[0] = fmax(fmin((int)(ratio.z * 255), 255), 0);
	comp[1] = fmax(fmin((int)(ratio.y * 255), 255), 0);
	comp[2] = fmax(fmin((int)(ratio.x * 255), 255), 0);
	put_pixel(pos, env->img, hex_col);
}

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
	if (light->type == DIRECTIONNAL)
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
	ratio = intensity * dot_vec4(pix->normal, dir);
	col.z = fmax(0, diff.z * light->diff_i.z * ratio);
	col.y = fmax(0, diff.y * light->diff_i.y * ratio);
	col.x = fmax(0, diff.x * light->diff_i.x * ratio);
	return (col);
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

int		shadow(t_args *args, t_pixel *pix, t_light *light)
{
	t_ray		light_ray;
	t_obj_lst	*objs;
	t_inter		inter;

	objs = args->scene->objs;
	if (light->type == DIRECTIONNAL)
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
	light_ray.orig = add_vec4(pix->inter.p, dmult_vec4(pix->normal, 0.000007));
	light_ray.orig.w = 1;
	inter = trace_ray(light_ray, args->scene->objs, args->obj_fct, 1);
	if (inter.dist < light_ray.range)
		return (0);
	return (1);	
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

t_vec3	specular_phong(t_pixel *pix, t_light *light)
{
	t_vec3	ratio;
	t_vec4	r;
	t_vec4	ldir;
	double	ndotl;

	ldir = normalize_vec4(rev_vec4(sub_vec4(pix->inter.p, light->vec)));
	ndotl = 2 * dot_vec4(pix->normal, ldir);
	r = normalize_vec4(sub_vec4(dmult_vec4(pix->normal, ndotl), ldir));
	ratio.x = light->spec_i.x * pix->inter.obj->material.spec.x *
		(pow(dot_vec4(pix->normal, r), pix->inter.obj->material.shin));
	ratio.y = light->spec_i.y * pix->inter.obj->material.spec.y *
		(pow(dot_vec4(pix->normal, r), pix->inter.obj->material.shin));
	ratio.z = light->spec_i.z * pix->inter.obj->material.spec.z *
		(pow(dot_vec4(pix->normal, r), pix->inter.obj->material.shin));
	return (ratio);
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
					args->spec_fct[pix->inter.obj->material.model - 1](pix, (t_light*)light->content));
				}
			}
			light = light->next;
		}
		pix->amb_ratio = add_vec3(pix->amb_ratio,
			mult_vec3(pix->inter.obj->material.amb, args->scene->amb_i));
	}
	process_color(args->env, pix, pos);
}

/*void	phong_model(t_args *args, t_light *lgt, size_t size)
{
	t_pixel	*pix;
	t_list	*light;
	int		vis;
	size_t	i;

	lgt = NULL;
	pix = args->pix_buf;
	vis = 1;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj && pix[i].inter.obj->material.model == PHONG)
		{
			light = args->scene->light;
			while (light)
			{
				if (args->scene->shd[SHADOW])
					vis = shadow(args, &pix[i], (t_light*)light->content);
				if (vis)
				{
					pix[i].col_ratio = add_vec3(pix[i].col_ratio,
						diffuse_lambert(&pix[i], (t_light*)light->content));
				}
					pix[i].col_ratio = add_vec3(pix[i].col_ratio,
						specular_phong(&pix[i], (t_light*)light->content));
				light = light->next;
			}
			pix[i].col_ratio = add_vec3(pix[i].col_ratio,
				mult_vec3(pix[i].inter.obj->material.amb, args->scene->amb_i));
		}
		++i;
	}
}*/
