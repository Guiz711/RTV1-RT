/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:12:14 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/27 22:33:55 by gmichaud         ###   ########.fr       */
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
	pix.y = pos / (double)env->win_width + 0.5;
	pix.x = pos - ((pix.y - 0.5) * (double)env->win_width) + 0.5;
	pix = ft_ndc_conv_2(pix, (double)env->win_width, (double)env->win_height);
	ray.dir = normalize_vec4(init_vec4(
		(2 * pix.x - 1) * tan(RAD(fovy / 2)) * scale,
		(1 - 2 * pix.y) * tan(RAD(fovy / 2)), -1, 0));
	ray.orig = init_vec4(0, 0, 0, 1);
	return (ray);
}

t_pixel			*create_ray_array(t_env *env, t_mtx4 v2w)
{
	size_t	len;
	size_t	pos;
	t_pixel	*pix_buf;

	len = WIN_WIDTH * WIN_HEIGHT;
	if (!(pix_buf = (t_pixel*)malloc(sizeof(*pix_buf) * len)))
		return (NULL);
	pos = 0;
	while (pos < len)
	{
		pix_buf[pos].p_ray = init_ray(env, pos);
		pix_buf[pos].p_ray.orig = new_coord(pix_buf[pos].p_ray.orig, v2w);
		pix_buf[pos].p_ray.dir = new_coord(pix_buf[pos].p_ray.dir, v2w);
		pix_buf[pos].inter.dist = 1e6;
		pix_buf[pos].inter.obj = NULL;
		pix_buf[pos].inter.p = init_vec4(0, 0, 0, 1);
		pix_buf[pos].normal = init_vec4(0, 0, 0, 0);
		pix_buf[pos].col_ratio = init_vec3(0, 0, 0);
		++pos;
	}
	return (pix_buf);
}