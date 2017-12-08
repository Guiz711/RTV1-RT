/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:39:08 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/08 13:32:52 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_sph_distance(t_poly2 poly)
{
	double	res;
	double	dist_1;
	double	dist_2;

	if (poly.disc == 0)
		return (-0.5 * poly.b / poly.a);
	else
	{
		res = (poly.b > 0) ? -0.5 * (poly.b + sqrt(poly.disc))
			: -0.5 * (poly.b - sqrt(poly.disc));
		dist_1 = res / poly.a;
		dist_2 = poly.c / res;
	}
	return ((dist_1 < dist_2) ? dist_1 : dist_2);
}

double			sphere_intersection(t_ray ray, void *obj)
{
	t_vec4		diff;
	t_poly2		poly;
	t_sphere	*sph;

	sph = (t_sphere*)obj;
	diff = ft_init_vec4(ray.orig.x - sph->center.x, ray.orig.y - sph->center.y,
		ray.orig.z - sph->center.z, 0);
	poly.a = ft_dot_product(ray.dir, ray.dir);
	poly.b = 2 * ft_dot_product(ray.dir, diff);
	poly.c = ft_dot_product(diff, diff) - sph->radius * sph->radius;
	poly.disc = poly.b * poly.b - 4 * poly.a * poly.c;
	if (poly.disc < 0)
		return (-1);
	return (get_sph_distance(poly));
}

double			plane_intersection(t_ray ray, void *obj)
{
	t_vec4	diff;
	double	denom;
	double	dist;
	t_plane	*pln;

	pln = (t_plane*)obj;
	diff = ft_init_vec4(pln->p.x - ray.orig.x, pln->p.y - ray.orig.y,
		pln->p.z - ray.orig.z, 0);
	denom = ft_dot_product(ray.dir, pln->normal);
	if (denom > 1e-6)
	dist = ft_dot_product(diff, pln->normal) / denom;
	return (dist);
}