/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:00:30 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/22 11:22:30 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4	sphere_normal(t_ray ray, void *obj)
{
	t_sphere	*sph;
	t_vec4		normal;
	
	sph = (t_sphere*)obj;
	normal = init_vec4(ray.inter.x - sph->center.x,
		ray.inter.y - sph->center.y, ray.inter.z - sph->center.z, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	cylinder_normal(t_ray ray, void *obj)
{
	t_cylinder	*cyl;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cyl = (t_cylinder*)obj;
	diff = init_vec4(ray.orig.x - cyl->p.x, ray.orig.y - cyl->p.y,
		ray.orig.z - cyl->p.z, 0);
	m = dot_vec4(ray.dir, cyl->dir) * ray.inter_dist + dot_vec4(diff, cyl->dir);
	normal = init_vec4(ray.inter.x - cyl->p.x - cyl->dir.x * m,
		ray.inter.y - cyl->p.y - cyl->dir.y * m,
		ray.inter.z - cyl->p.z - cyl->dir.z * m, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	cone_normal(t_ray ray, void *obj)
{
	t_cone		*cone;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cone = (t_cone*)obj;
	diff = init_vec4(ray.orig.x - cone->p.x, ray.orig.y - cone->p.y,
		ray.orig.z - cone->p.z, 0);
	m = dot_vec4(ray.dir, cone->dir) * ray.inter_dist + dot_vec4(diff, cone->dir);
	normal = init_vec4(ray.inter.x - cone->p.x - cone->dir.x * m * cone->ang_tan,
		ray.inter.y - cone->p.y - cone->dir.y * m * cone->ang_tan,
		ray.inter.z - cone->p.z - cone->dir.z * m * cone->ang_tan, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	plane_normal(t_ray ray, void *obj)
{
	t_plane		*pln;
	t_vec4		normal;

	ray.color = ray.color;
	pln = (t_plane*)obj;
	if (dot_vec4(ray.dir, pln->normal) > 0)
		normal = normalize_vec4(init_vec4(-pln->normal.x, -pln->normal.y, -pln->normal.z, 0));
	else
		normal = normalize_vec4(init_vec4(pln->normal.x, pln->normal.y, pln->normal.z, 0));
	return (normal);
}
