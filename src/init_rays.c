/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:12:14 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/08 11:11:53 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec2	ft_ndc_conv_2(t_vec2 v)
{
	t_vec2 v_norm;
	
	v_norm.x = v.x / WIN_WIDTH;
	v_norm.y = v.y / WIN_HEIGHT;
	return (v_norm);
}

t_ray	init_ray(size_t pos)
{
	t_vec2	pix;
	t_ray	ray;
	double	scale;
	double	fovy;

	scale = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	fovy = (double)FOVX / scale;
	pix.y = pos / WIN_WIDTH + 0.5;
	pix.x = pos - ((pix.y - 0.5) * WIN_WIDTH) + 0.5;
	pix = ft_ndc_conv_2(pix);
	ray.dir.x = (2 * pix.x - 1) * tan(RAD(fovy / 2)) * scale;
	ray.dir.y = (1 - 2 * pix.y) * tan(RAD(fovy / 2));
	ray.dir.z = -1;
	ray.dir.w = 0;
	ray.dir = ft_normalize(ray.dir);
	ray.orig.x = 0;
	ray.orig.y = 0;
	ray.orig.z = 0;
	ray.orig.w = 1;
	return (ray);
}

t_ray	*create_ray_array(t_mtx4 v2w)
{
	size_t	len;
	size_t	pos;
	t_ray	*ray_list;

	len = WIN_WIDTH * WIN_HEIGHT;
	if (!(ray_list = (t_ray*)malloc(sizeof(*ray_list) * len)))
		return (NULL);
	pos = 0;
	while (pos < len)
	{
		ray_list[pos] = init_ray(pos);
		ray_list[pos].orig = new_coord(ray_list[pos].orig, v2w);
		ray_list[pos].dir = new_coord(ray_list[pos].dir, v2w);
		ray_list[pos].inter_dist = 1e6;
		ray_list[pos].inter_obj = NULL;
		pos++;
	}
	return (ray_list);
}