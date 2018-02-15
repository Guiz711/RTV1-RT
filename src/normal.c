/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:00:30 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/12 18:09:54 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4	sphere_normal(t_ray *ray, t_inter *inter)
{
	t_sphere	*sph;
	t_vec4		normal;

	ray = NULL;
	sph = (t_sphere*)inter->obj->content;
	normal = normalize_vec4(sub_vec4(inter->p, sph->center));
	return (normal);
}

t_vec4	cylinder_normal(t_ray *ray, t_inter *inter)
{
	t_cylinder	*cyl;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cyl = (t_cylinder*)inter->obj->content;
	diff = sub_vec4(ray->orig, cyl->p);
	m = dot_vec4(ray->dir, cyl->dir) * inter->dist
		+ dot_vec4(diff, cyl->dir);
	normal = init_vec4(inter->p.x - cyl->p.x - cyl->dir.x * m,
		inter->p.y - cyl->p.y - cyl->dir.y * m,
		inter->p.z - cyl->p.z - cyl->dir.z * m, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	cone_normal(t_ray *ray, t_inter *inter)
{
	t_cone		*cone;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cone = (t_cone*)inter->obj->content;
	diff = sub_vec4(ray->orig, cone->p);
	m = (dot_vec4(ray->dir, cone->dir) * inter->dist
		+ dot_vec4(diff, cone->dir)) * cone->ang_tan;
	normal = init_vec4(inter->p.x - cone->p.x - cone->dir.x * m,
		inter->p.y - cone->p.y - cone->dir.y * m,
		inter->p.z - cone->p.z - cone->dir.z * m, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	plane_normal(t_ray *ray, t_inter *inter)
{
	t_plane		*pln;
	t_vec4		normal;

	pln = (t_plane*)inter->obj->content;
	if (dot_vec4(ray->dir, pln->normal) > 0)
		normal = normalize_vec4(rev_vec4(pln->normal));
	else
		normal = normalize_vec4(pln->normal);
	return (normal);
}
