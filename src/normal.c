/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:00:30 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/10 10:30:56 by gmichaud         ###   ########.fr       */
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

t_vec4	cylinder_normal(t_ray ray, void *obj)
{
	t_cylinder	*cyl;
	t_vec4		inter;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cyl = (t_cylinder*)obj;
	inter = ft_init_vec4(ray.orig.x + ray.dir.x * ray.inter_dist,
		ray.orig.y + ray.dir.y * ray.inter_dist,
		ray.orig.z + ray.dir.z * ray.inter_dist, 1);
	diff = ft_init_vec4(ray.orig.x - cyl->p.x, ray.orig.y - cyl->p.y,
		ray.orig.z - cyl->p.z, 0);
	m = ft_dot_product(ray.dir, cyl->dir) * ray.inter_dist + ft_dot_product(diff, cyl->dir);
	normal = ft_init_vec4(inter.x - cyl->p.x - cyl->dir.x * m,
		inter.y - cyl->p.y - cyl->dir.y * m, inter.z - cyl->p.z - cyl->dir.z * m, 0);
	normal = ft_normalize(normal);
	return (normal);
}

t_vec4	cone_normal(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_vec4		inter;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cone = (t_cone*)obj;
	inter = ft_init_vec4(ray.orig.x + ray.dir.x * ray.inter_dist,
		ray.orig.y + ray.dir.y * ray.inter_dist,
		ray.orig.z + ray.dir.z * ray.inter_dist, 1);
	diff = ft_init_vec4(ray.orig.x - cone->p.x, ray.orig.y - cone->p.y,
		ray.orig.z - cone->p.z, 0);
	m = ft_dot_product(ray.dir, cone->dir) * ray.inter_dist + ft_dot_product(diff, cone->dir);
	normal = ft_init_vec4(inter.x - cone->p.x - cone->dir.x * m * cone->ang_tan,
		inter.y - cone->p.y - cone->dir.y * m * cone->ang_tan,
		inter.z - cone->p.z - cone->dir.z * m * cone->ang_tan, 0);
	normal = ft_normalize(normal);
	return (normal);
}

t_vec4	plane_normal(t_ray ray, void *obj)
{
	t_plane		*pln;
	t_vec4		normal;

	ray.color = ft_init_vec3(0, 0, 0);
	pln = (t_plane*)obj;
	normal = ft_normalize(ft_init_vec4(-pln->normal.x, -pln->normal.y, -pln->normal.z, 0));
	return (normal);
}
