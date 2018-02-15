/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:39:08 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/15 15:20:09 by gmichaud         ###   ########.fr       */
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
	if (dist_1 < 0)
		return (dist_2);
	if (dist_2 < 0)
		return (dist_1);
	return ((dist_1 < dist_2) ? dist_1 : dist_2);
}

double			sphere_intersection(t_ray ray, void *obj)
{
	t_vec4		diff;
	t_poly2		poly;
	t_sphere	*sph;

	sph = (t_sphere*)obj;
	diff = sub_vec4(ray.orig, sph->center);
	poly.a = dot_vec4(ray.dir, ray.dir);
	poly.b = 2 * dot_vec4(ray.dir, diff);
	poly.c = dot_vec4(diff, diff) - sph->radius * sph->radius;
	poly.disc = poly.b * poly.b - 4 * poly.a * poly.c;
	if (poly.disc < 0)
		return (-1);
	return (get_sph_distance(poly));
}

double			cylinder_intersection(t_ray ray, void *obj)
{
	t_vec4		diff;
	t_poly2		poly;
	t_cylinder	*cyl;
	double		dot1;
	double		dot2;
	
	cyl = (t_cylinder*)obj;
	diff = sub_vec4(ray.orig, cyl->p);
	dot1 = dot_vec4(ray.dir, cyl->dir);
	dot2 = dot_vec4(diff, cyl->dir);
	poly.a = dot_vec4(ray.dir, ray.dir) - SQUARE(dot1);
	poly.b = 2 * (dot_vec4(ray.dir, diff) - dot1 * dot2);
	poly.c = dot_vec4(diff, diff) - SQUARE(dot2) - SQUARE(cyl->radius);
	poly.disc = SQUARE(poly.b) - 4 * poly.a * poly.c;
	if (poly.disc < 0)
		return (-1);
	return (get_sph_distance(poly));
}

double			cone_intersection(t_ray ray, void *obj)
{
	t_vec4		diff;
	t_poly2		poly;
	t_cone		*cone;
	double		dot1;
	double		dot2;
	
	cone = (t_cone*)obj;
	diff = sub_vec4(ray.orig, cone->p);
	dot1 = dot_vec4(ray.dir, cone->dir);
	dot2 = dot_vec4(diff, cone->dir);
	poly.a = dot_vec4(ray.dir, ray.dir) - cone->ang_tan * SQUARE(dot1);
	poly.b = 2 * (dot_vec4(ray.dir, diff) - cone->ang_tan * dot1 * dot2);
	poly.c = dot_vec4(diff, diff) - cone->ang_tan * SQUARE(dot2);
	poly.disc = SQUARE(poly.b) - 4 * poly.a * poly.c;
	if (poly.disc < 0)
		return (-1);
	return (get_sph_distance(poly));
}

double			plane_intersection(t_ray ray, void *obj)
{
	t_vec4	diff;
	double	denom;
	double	frac;
	double	dist;
	t_plane	*pln;

	pln = (t_plane*)obj;
	diff = sub_vec4(ray.orig, pln->p);
	frac = dot_vec4(diff, pln->normal);
	denom = dot_vec4(ray.dir, pln->normal);
	if ((denom > 1e-6 && frac < 0) || (denom < 1e6 && frac > 0))
		dist =  -frac / denom;
	else
		dist = -1;
	return (dist);
}
