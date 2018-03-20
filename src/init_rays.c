/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:18:11 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 14:49:14 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec2	ft_ndc_conv_2(t_vec2 v, int win_width, int win_height)
{
	t_vec2	v_norm;

	v_norm.x = v.x / win_width;
	v_norm.y = v.y / win_height;
	return (v_norm);
}

static t_ray	init_ray(t_env *env, size_t pos)
{
	t_vec2	pix;
	t_ray	ray;
	double	scale;
	double	fovy;

	scale = (double)env->win_width / (double)env->win_height;
	fovy = (double)env->fov / scale;
	pix.y = pos / env->win_width + 0.5;
	pix.x = pos - ((pix.y - 0.5) * env->win_width) + 0.5;
	pix = ft_ndc_conv_2(pix, (double)env->win_width, (double)env->win_height);
	ray.dir = normalize_vec4(init_vec4(
				(2 * pix.x - 1) * tan(rad(fovy / 2)) * scale,
				(1 - 2 * pix.y) * tan(rad(fovy / 2)), -1, 0));
	ray.orig = init_vec4(0, 0, 0, 1);
	return (ray);
}

static void		init_pixel(t_pixel *pixel, t_env *env, t_mtx4 v2w, size_t pos)
{
	pixel->p_ray = init_ray(env, pos);
	pixel->p_ray.orig = new_coord(pixel->p_ray.orig, v2w);
	pixel->p_ray.dir = new_coord(pixel->p_ray.dir, v2w);
	pixel->p_ray.range = 1e6;
	pixel->inter.dist = 1e6;
	pixel->inter.obj = NULL;
	pixel->inter.p = init_vec4(0, 0, 0, 1);
	pixel->inter.normal = init_vec4(0, 0, 0, 0);
	pixel->color.amb_ratio = init_vec3(0, 0, 0);
	pixel->color.diff_ratio = init_vec3(0, 0, 0);
	pixel->color.spec_ratio = init_vec3(0, 0, 0);
}

t_pixel			*init_pix_buffer(t_env *env, t_mtx4 v2w)
{
	size_t	len;
	size_t	pos;
	t_pixel	*pix_buf;

	env->win_width = WIN_WIDTH / env->aliasing;
	env->win_height = WIN_HEIGHT / env->aliasing;
	if (env->aliasing <= 1)
		len = (env->win_height * env->win_width) / env->aliasing;
	else
		len = (env->win_height * env->win_width);
	if (!(pix_buf = (t_pixel*)malloc(sizeof(*pix_buf) * len)))
	{
		env->win_width = WIN_WIDTH;
		env->win_height = WIN_HEIGHT;
		return (NULL);
	}
	pos = 0;
	while (pos < len)
	{
		init_pixel(&pix_buf[pos], env, v2w, pos);
		pos++;
	}
	env->win_width = WIN_WIDTH;
	env->win_height = WIN_HEIGHT;
	return (pix_buf);
}
