/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:12:14 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/27 13:57:18 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec2	ft_ndc_conv_2(t_vec2 v, int win_width, int win_height)
{
	t_vec2 v_norm;
	
	v_norm.x = v.x / win_width;
	v_norm.y = v.y / win_height;
	return (v_norm);
}

t_ray	init_ray(t_env *env, size_t pos)
{
	t_vec2	pix;
	t_ray	ray;
	double	scale;
	double	fovy;

	scale = (double)env->win_width / (double)env->win_height;
	fovy = (double)env->fov / scale;
	pix.y = pos / (double)env->win_width + 0.5;
	pix.x = pos - ((pix.y - 0.5) * env->win_width) + 0.5;
	pix = ft_ndc_conv_2(pix, env->win_width, env->win_height);
	ray.dir.x = (2 * pix.x - 1) * tan(RAD(fovy / 2)) * scale;
	ray.dir.y = (1 - 2 * pix.y) * tan(RAD(fovy / 2));
	ray.dir.z = -1;
	ray.dir.w = 0;
	ray.dir = normalize_vec4(ray.dir);
	ray.orig.x = 0;
	ray.orig.y = 0;
	ray.orig.z = 0;
	ray.orig.w = 1;
	return (ray);
}

t_pixel		*create_ray_array(t_env *env, t_mtx4 v2w)
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
		pix_buf[pos].inter_dist = 1e6;
		pix_buf[pos].inter_obj = NULL;
		pix_buf[pos].col_ratio = init_vec3(0, 0, 0);
		pix_buf[pos].normal = init_vec4(0, 0, 0, 0);
		pix_buf[pos].inter = init_vec4(0, 0, 0, 1);
		pos++;
	}
	return (pix_buf);
}