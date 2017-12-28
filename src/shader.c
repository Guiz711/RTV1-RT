/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:46:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/28 17:33:31 by gmichaud         ###   ########.fr       */
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

void	fill_img_buffer(t_env *env, t_pixel *pix)
{
	size_t		i;
	size_t		size;
	uint32_t	hex_col;
	unsigned	char *comp;

	size = env->win_width * env->win_height;
	i = 0;
	while (i < size)
	{
		hex_col = 0;
		comp = (unsigned char*)&hex_col;
		comp[0] = fmax(fmin((int)(pix[i].col_ratio.z * 255), 255), 0);
		comp[1] = fmax(fmin((int)(pix[i].col_ratio.y * 255), 255), 0);
		comp[2] = fmax(fmin((int)(pix[i].col_ratio.x * 255), 255), 0);
		put_pixel(i, env->img, hex_col);
		++i;
	}
}

void	raw_color(t_pixel *pix, t_scene *scn, t_light *lgt, size_t size)
{
	size_t	i;

	scn = NULL;
	lgt = NULL;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj)
			pix[i].col_ratio = dmult_vec3(pix[i].inter.obj->material.amb, 1);
		++i;
	}
}

void	facing_ratio(t_pixel *pix, t_scene *scn, t_light *lgt, size_t size)
{
	size_t	i;
	double	dot;

	scn = NULL;
	lgt = NULL;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj)
		{
			dot = fmax(0, -dot_vec4(pix[i].normal, pix[i].p_ray.dir));
			pix[i].col_ratio = dmult_vec3(pix[i].inter.obj->material.amb, dot);
		}
		++i;
	}
}

int		shadow(t_pixel *pix, t_scene *scn, t_light *light)
{
	t_ray		light_ray;
	t_obj_lst	*objs;
	double		inter;

	objs = scn->objs;
	if (light->type == DIRECTIONNAL)
	{
		light_ray.dir = rev_vec4(light.vec);
		light_ray.inter_dist = 1e6;
	}
	else
	{
		light_ray.dir = rev_vec4(sub_vec4(ray->inter, light.vec));;
		light_ray.inter_dist = norm_vec4(light_ray.dir);
		light_ray.dir = normalize_vec4(light_ray.dir);
	}
	light_ray.orig = init_vec4(ray->inter.x + ray->obj_normal.x * 0.000007,
		ray->inter.y + ray->obj_normal.y * 0.000007,
		ray->inter.z + ray->obj_normal.z * 0.000007, 1);
	while (objs)
	{
		inter = args->obj_fct[objs->content_type](light_ray, (void*)objs->content);
		if (inter > 0 && inter < light_ray.inter_dist)
			return (0);
		objs = objs->next;
	}
	return (1);	
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
		intensity = light->range;
	}
	else
	{
		dir = rev_vec4(sub_vec4(pix->inter.p, light->vec));
		intensity = light->range / (4 * M_PI * norm_vec4(dir));
		dir = normalize_vec4(dir);
	}
	ratio = intensity * dot_vec4(pix->normal, dir);
	col.z = fmax(0, diff.z / M_PI * light->diff_i.z * ratio);
	col.y = fmax(0, diff.y / M_PI * light->diff_i.y * ratio);
	col.x = fmax(0, diff.x / M_PI * light->diff_i.x * ratio);
	return (col);
}

void	lambert_model(t_pixel *pix, t_scene *scn, t_light *lgt, size_t size)
{
	size_t	i;
	t_list	*light;

	lgt = NULL;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj)
		{
			light = scn->light;
			while (light)
			{
				if (shadow
				pix[i].col_ratio = add_vec3(pix[i].col_ratio,
					diffuse_lambert(&pix[i], (t_light*)light->content));
				light = light->next;
			}
		}
		++i;
	}
}

void	manage_lighting(t_args *args, size_t size)
{
	size_t	i;

	i = 3;
	while (i < COUNT_SHD)
	{
		if (args->scene->shd[i])
		{
			args->shd_fct[i](args->pix_buf, args->scene, NULL, size);
		}
		++i;
	}
}

int		manage_shaders(t_args *args)
{
	t_scene	*scn;
	size_t	size;

	scn = args->scene;
	size = args->env->win_width * args->env->win_height;
	if (scn->shd[NO_SHD])
		args->shd_fct[NO_SHD](args->pix_buf, args->scene, NULL, size);
	else if (scn->shd[FACING])
		args->shd_fct[FACING](args->pix_buf, args->scene, NULL, size);
	else
		manage_lighting(args, size);
	fill_img_buffer(args->env, args->pix_buf);
	return (0);
}
