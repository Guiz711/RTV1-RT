/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:31:33 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/21 10:09:50 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	reflected_ray(t_vec4 ray_dir, t_inter *inter)
{
	double	ndotr;
	t_ray	refl;

	ndotr = dot_vec4(inter->normal, ray_dir);
	refl.dir = normalize_vec4(add_vec4(ray_dir,
		dmult_vec4(inter->normal, -2 * ndotr)));
	refl.orig = add_vec4(inter->p, dmult_vec4(inter->normal, 0.0000007));
	refl.range = 1e6;
	refl.inside = 0;
	return (refl);
}

t_ray	refracted_ray(t_vec4 ray_dir, t_inter *inter)
{
	t_ray	refr;
	double	r_ratio;
	double	c1;
	double	c2;

	c1 = dot_vec4(inter->normal, ray_dir);
	if (c1 < 0)
	{
		r_ratio = 1 / inter->obj->material.refract;
		c2 = sqrt(1 - SQUARE(r_ratio) * (1 - SQUARE(-c1)));
		refr.dir = add_vec4(dmult_vec4(ray_dir, r_ratio),
			dmult_vec4(inter->normal, (r_ratio * -c1) - c2));
		refr.orig = add_vec4(inter->p, dmult_vec4(inter->normal, -0.0000007));
		refr.inside = 0;
	}
	else
	{
		r_ratio = inter->obj->material.refract;
		c2 = sqrt(1 - SQUARE(r_ratio) * (1 - SQUARE(c1)));
		refr.dir = add_vec4(dmult_vec4(ray_dir, r_ratio),
			dmult_vec4(rev_vec4(inter->normal), (r_ratio * c1) - c2));
		refr.orig = add_vec4(inter->p, dmult_vec4(inter->normal, 0.0000007));
		refr.inside = 1;
	}
	refr.range = 1e6;
	return (refr);
}

double	fresnel_calc(t_vec4 normal, t_vec4 ray_dir, double n1, double n2)
{
	double	refl;
	double	ndotr;
	double	r0;
	double	ratio;
	double 	sinx;

	ndotr = dot_vec4(normal, ray_dir);
	if (ndotr < 0)
		invert(&n1, &n2);
	ndotr = dot_vec4(normal, ray_dir);
	r0 = SQUARE((n1 - n2) / (n1 + n2));
	if (n2 > n1)
	{
		ratio = n2 / n1;
		sinx = SQUARE(ratio) * (1 - SQUARE(ndotr));
		if (sinx > 1)
			return (1);
		ndotr = -sqrt(1 - sinx);
	}
	refl = r0 + (1 - r0) * pow((1 + ndotr), 5);
	return (refl);
}