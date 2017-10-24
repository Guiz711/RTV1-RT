/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:12:14 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/24 17:13:52 by gmichaud         ###   ########.fr       */
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

t_ray	init_ray(size_t i)
{
	t_vec2	pix;
	t_ray	ray;

	pix.y = i / WIN_WIDTH + 0.5;
	pix.x = i - ((pix.y - 0.5) * WIN_WIDTH) + 0.5;
	pix = ft_ndc_conv_2(pix);
	ray.dir.x = (2 * pix.x - 1) * (WIN_WIDTH / WIN_HEIGHT) * tan(RAD(FOVY / 2));
	ray.dir.y = (1 - 2 * pix.y) * tan(RAD(FOVY / 2));
	ray.dir.z = -1;
	ray.dir.w = 0;
	ray.dir = ft_normalize(ray.dir);
	ray.orig.x = 0;
	ray.orig.y = 0;
	ray.orig.z = 0;
	ray.orig.w = 1;
	return (ray);
}

t_ray	*create_ray_buffer(t_mtx4 *v2w)
{
	size_t	len;
	size_t	i;
	t_ray	*buf;

	len = WIN_WIDTH * WIN_HEIGHT;
	if (!(buf = (t_ray*)malloc(sizeof(*buf) * len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		buf[i] = init_ray(i);
		if (v2w)
		{
			buf[i].orig = new_coord(buf[i].orig, *v2w);
			buf[i].dir = new_coord(buf[i].dir, *v2w);
		}
		printf("%f : %f\n", buf[i].orig.x, buf[i].orig.y);
		i++;
	}
	return (buf);
}