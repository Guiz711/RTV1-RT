/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:15:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 16:17:06 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

t_vec4	paraboloid_normal(t_ray *ray, t_inter *inter)
{
	t_parab		*parab;
	t_vec4		diff;
	double		m;
	t_vec4		normal;

	ray = NULL;
	parab = (t_parab*)inter->obj->content;
	diff = sub_vec4(inter->p, parab->p);
	m = dot_vec4(diff, parab->dir);
	normal = sub_vec4(diff,
		dmult_vec4(parab->dir, m + parab->k));
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

t_vec4	triangle_normal(t_ray *ray, t_inter *inter)
{
	t_triangle	*tri;
	t_vec4		normal;

	tri = (t_triangle*)inter->obj->content;
	if (dot_vec4(ray->dir, tri->normal) > 0)
		normal = normalize_vec4(rev_vec4(tri->normal));
	else
		normal = normalize_vec4(tri->normal);
	return (normal);
}
