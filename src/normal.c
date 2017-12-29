/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:00:30 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/29 13:44:12 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4	sphere_normal(t_pixel *pixel)
{
	t_sphere	*sph;
	t_ray		*ray;
	t_inter		*inter;
	t_vec4		normal;

	sph = (t_sphere*)pixel->inter.obj->content;
	ray = &pixel->p_ray;
	inter = &pixel->inter;
	normal = normalize_vec4(sub_vec4(inter->p, sph->center));
	//printf("%f; %f; %f\n", normal.z, inter->p.z, sph->center.z);
	return (normal);
}

t_vec4	cylinder_normal(t_pixel *pixel)
{
	t_cylinder	*cyl;
	t_ray		*ray;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cyl = (t_cylinder*)pixel->inter.obj->content;
	ray = &pixel->p_ray;
	diff = sub_vec4(ray->orig, cyl->p);
	m = dot_vec4(ray->dir, cyl->dir) * pixel->inter.dist
		+ dot_vec4(diff, cyl->dir);
	normal = init_vec4(pixel->inter.p.x - cyl->p.x - cyl->dir.x * m,
		pixel->inter.p.y - cyl->p.y - cyl->dir.y * m,
		pixel->inter.p.z - cyl->p.z - cyl->dir.z * m, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	cone_normal(t_pixel *pixel)
{
	t_cone		*cone;
	t_ray		*ray;
	t_vec4		diff;
	double		m;
	t_vec4		normal;
	
	cone = (t_cone*)pixel->inter.obj->content;
	ray = &pixel->p_ray;
	diff = sub_vec4(ray->orig, cone->p);
	m = (dot_vec4(ray->dir, cone->dir) * pixel->inter.dist
		+ dot_vec4(diff, cone->dir)) * cone->ang_tan;
	//normal = sub_vec4(pixel->inter.p, sub_vec4(cone->p,
		//dmult_vec4(cone->dir, m)));
	normal = init_vec4(pixel->inter.p.x - cone->p.x - cone->dir.x * m,
		pixel->inter.p.y - cone->p.y - cone->dir.y * m,
	pixel->inter.p.z - cone->p.z - cone->dir.z * m, 0);
	normal = normalize_vec4(normal);
	return (normal);
}

t_vec4	plane_normal(t_pixel *pixel)
{
	t_plane		*pln;
	t_vec4		normal;

	pln = (t_plane*)pixel->inter.obj->content;
	if (dot_vec4(pixel->p_ray.dir, pln->normal) > 0)
		normal = normalize_vec4(rev_vec4(pln->normal));
	else
		normal = normalize_vec4(pln->normal);
	return (normal);
}
