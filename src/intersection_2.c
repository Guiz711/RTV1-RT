/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:19:47 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 14:48:57 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			paraboloid_intersection(t_ray ray, void *obj)
{
	t_vec4		diff;
	t_poly2		poly;
	t_parab		*parab;
	double		dot1;
	double		dot2;

	parab = (t_parab*)obj;
	diff = sub_vec4(ray.orig, parab->p);
	dot1 = dot_vec4(ray.dir, parab->dir);
	dot2 = dot_vec4(diff, parab->dir);
	poly.a = dot_vec4(ray.dir, ray.dir) - square(dot1);
	poly.b = 2 * (dot_vec4(ray.dir, diff) - dot1 * (dot2 + 2 * parab->k));
	poly.c = dot_vec4(diff, diff) - dot2 * (dot2 + 4 * parab->k);
	poly.disc = square(poly.b) - 4 * poly.a * poly.c;
	if (poly.disc < 0)
		return (-1);
	return (resolve_poly2(poly));
}

t_vec4			get_triangle_normal(t_vec4 p1, t_vec4 p2, t_vec4 p3)
{
	t_vec4	p1p2;
	t_vec4	p1p3;
	t_vec4	nrm;

	p1p2 = sub_vec4(p2, p1);
	p1p3 = sub_vec4(p3, p1);
	nrm = cross_vec4(p1p2, p1p3);
	nrm.w = 0;
	return (normalize_vec4(nrm));
}

static double	objplane_intersection(t_ray ray, t_vec4 normal, t_vec4 p)
{
	t_vec4	diff;
	double	denom;
	double	frac;
	double	dist;

	diff = sub_vec4(ray.orig, p);
	frac = dot_vec4(diff, normal);
	denom = dot_vec4(ray.dir, normal);
	if ((denom > 1e-6 && frac < 0) || (denom < 1e6 && frac > 0))
		dist = -frac / denom;
	else
		dist = -1;
	return (dist);
}

double			triangle_intersection(t_ray ray, void *obj)
{
	double		dist;
	t_triangle	*tri;
	t_vec4		p;
	t_vec4		c;
	t_vec4		edge;

	tri = (t_triangle*)obj;
	if ((dist = objplane_intersection(ray, tri->normal, tri->p1)) == -1)
		return (-1);
	p = add_vec4(ray.orig, dmult_vec4(ray.dir, dist));
	edge = sub_vec4(tri->p2, tri->p1);
	c = cross_vec4(edge, sub_vec4(p, tri->p1));
	if (dot_vec4(tri->normal, c) < 0)
		return (-1);
	edge = sub_vec4(tri->p3, tri->p2);
	c = cross_vec4(edge, sub_vec4(p, tri->p2));
	if (dot_vec4(tri->normal, c) < 0)
		return (-1);
	edge = sub_vec4(tri->p1, tri->p3);
	c = cross_vec4(edge, sub_vec4(p, tri->p3));
	if (dot_vec4(tri->normal, c) < 0)
		return (-1);
	return (dist);
}
