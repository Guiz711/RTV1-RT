/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:39:08 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/07 19:44:33 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_sph_distance(double a, double b, double c, double disc)
{
	double	res;
	double	dist_1;
	double	dist_2;

	if (disc == 0)
		return (-0.5 * b / a);
	else
	{
		res = (b > 0) ? -0.5 * (b + sqrt(disc)) : -0.5 * (b - sqrt(disc));
		dist_1 = res / a;
		dist_2 = c / res;
	}
	return ((dist_1 < dist_2) ? dist_1 : dist_2);
}

double			sphere_intersection(t_ray ray, t_sphere sph)
{
	t_vec4	diff;
	double	a;
	double	b;
	double	c;
	double	disc;

	diff = ft_init_vec4(ray.orig.x - sph.center.x, ray.orig.y - sph.center.y,
		ray.orig.z - sph.center.z, 0);
	a = ft_dot_product(ray.dir, ray.dir);
	b = 2 * ft_dot_product(ray.dir, diff);
	c = ft_dot_product(diff, diff) - sph.radius * sph.radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1);
	return (get_sph_distance(a, b, c, disc));
}

double			plane_intersection(t_ray ray, t_plane pln)
{
	t_vec4	diff;
	double	denom;
	double	dist;

	diff = ft_init_vec4(pln.p.x - ray.orig.x, pln.p.y - ray.orig.y,
		pln.p.z - ray.orig.z, 0);
	denom = ft_dot_product(ray.dir, pln.normal);
	if (denom > 1e-6)
	dist = ft_dot_product(diff, pln.normal) / denom;
	return (dist);
}