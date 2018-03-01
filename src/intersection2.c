/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurla <arthurla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 18:38:52 by arthurla          #+#    #+#             */
/*   Updated: 2018/03/01 16:12:17 by arthurlabelle    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	triPlane_intersection(t_ray ray, t_vec4 normal, t_vec4 p)
{
	t_vec4	diff;
	double	denom;
	double	frac;
	double	dist;

	diff = sub_vec4(ray.orig, p);
	frac = dot_vec4(diff, normal);
	denom = dot_vec4(ray.dir, normal);
	if ((denom > 1e-6 && frac < 0) || (denom < 1e6 && frac > 0))
		dist =  -frac / denom;
	else
		dist = -1;
	return (dist);
}

t_vec4  			get_triangle_normal(t_vec4 p1, t_vec4 p2, t_vec4 p3)
{
	t_vec4	p1p2;
	t_vec4	p1p3;
	t_vec4	nrm;

	p1p2 = sub_vec4(p2, p1);
	p1p3 = sub_vec4(p3, p1);
	nrm = cross_vec4(p1p2, p1p3);
	nrm.w = 0;
	return(normalize_vec4(nrm));
}

double				triangle_intersection(t_ray ray, void *obj)
{
	double dist;
	t_triangle *tri;
	t_vec4 P;
	t_vec4 C;
	t_vec4 edge;

	tri = (t_triangle*)obj;
	if ((dist = triPlane_intersection(ray, tri->normal, tri->p1)) == -1)
		return (-1);
	P = add_vec4(ray.orig, dmult_vec4(ray.dir, dist));
	edge = sub_vec4(tri->p2, tri->p1);
	C = cross_vec4(edge, sub_vec4(P, tri->p1));
	if (dot_vec4(tri->normal, C) < 0)
		return (-1);
	edge = sub_vec4(tri->p3, tri->p2);
	C = cross_vec4(edge, sub_vec4(P, tri->p2));
	if (dot_vec4(tri->normal, C) < 0)
		return (-1);
	edge = sub_vec4(tri->p1, tri->p3);
	C = cross_vec4(edge, sub_vec4(P, tri->p3));
	if (dot_vec4(tri->normal, C) < 0)
		return (-1);
	return (dist);
}
