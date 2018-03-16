/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:31:33 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/16 12:07:51 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_ray	ray_in(t_vec4 ray_dir, t_inter *inter, double c1)
{
	t_ray	refr;
	double	r_ratio;
	double	c2;

	r_ratio = 1 / inter->obj->material.refract;
	c2 = sqrt(1 - SQUARE(r_ratio) * (1 - SQUARE(-c1)));
	refr.dir = add_vec4(dmult_vec4(ray_dir, r_ratio),
		dmult_vec4(inter->normal, (r_ratio * -c1) - c2));
	refr.orig = add_vec4(inter->p, dmult_vec4(inter->normal, -0.0000007));
	refr.inside = 0;
	refr.range = 1e6;
	return (refr);
}

static t_ray	ray_out(t_vec4 ray_dir, t_inter *inter, double c1)
{
	t_ray	refr;
	double	r_ratio;
	double	c2;

	r_ratio = inter->obj->material.refract;
	c2 = sqrt(1 - SQUARE(r_ratio) * (1 - SQUARE(c1)));
	refr.dir = add_vec4(dmult_vec4(ray_dir, r_ratio),
		dmult_vec4(rev_vec4(inter->normal), (r_ratio * c1) - c2));
	refr.orig = add_vec4(inter->p, dmult_vec4(inter->normal, 0.0000007));
	refr.inside = 1;
	refr.range = 1e6;
	return (refr);
}

t_ray			refracted_ray(t_vec4 ray_dir, t_inter *inter)
{
	double	c1;

	c1 = dot_vec4(inter->normal, ray_dir);
	if (c1 < 0)
		return (ray_in(ray_dir, inter, c1));
	else
		return (ray_out(ray_dir, inter, c1));
}

t_ray			reflected_ray(t_vec4 ray_dir, t_inter *inter)
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
