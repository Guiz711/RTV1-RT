/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:02:24 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/08 13:47:13 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4	sphere_normal(t_ray ray, void *obj)
{
	t_sphere	*sph;
	t_vec4		inter;
	t_vec4		normal;
	
	sph = (t_sphere*)obj;
	inter = ft_init_vec4(ray.orig.x + ray.dir.x * ray.inter_dist,
		ray.orig.y + ray.dir.y * ray.inter_dist,
		ray.orig.z + ray.dir.z * ray.inter_dist, 1);
	normal = ft_init_vec4(inter.x - sph->center.x,
		inter.y - sph->center.y, inter.z - sph->center.z, 0);
	normal = ft_normalize(normal);
	return (normal);
}

void	check_intersections(t_ray *ray, t_obj_lst *objs, t_inter_fct *obj_fct)
{
	double	inter;

	while (objs)
	{
		inter = obj_fct[objs->content_type](*ray, (void*)objs->content);
		if (inter < ray->inter_dist && inter != -1)
		{
			ray->inter_dist = inter;
			ray->inter_obj = objs->content;
		}
		objs = objs->next;
	}
	if (ray->inter_obj->content_type == SPHERE)
		ray->obj_normal = sphere_normal(*ray, ray->inter_obj->content);
}

int		raytracing(t_args *args)
{
	size_t		i;
	t_obj_lst	*obj;
	double		dist;
	t_sphere	*sph;	
	t_vec4		inter;
	t_vec4		normal;
	double		f_ratio;

	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		check_intersections(&(args->ray_buf[i]), args->scene->objs,
			args->obj_fct);
		if (obj)
		{
			f_ratio = ft_dot_product(normal, ft_init_vec4(-ray_list[i].dir.x,
				-ray_list[i].dir.y, -ray_list[i].dir.z, 0));
			put_pixel(i, env->img, shade(((t_sphere*)obj->content)->color, f_ratio));
		}
		++i;
	}
	return (0);
}