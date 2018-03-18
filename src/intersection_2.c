/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:19:47 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 18:19:49 by jgourdin         ###   ########.fr       */
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
	poly.a = dot_vec4(ray.dir, ray.dir) - SQUARE(dot1);
	poly.b = 2 * (dot_vec4(ray.dir, diff) - dot1 * (dot2 + 2 * parab->k));
	poly.c = dot_vec4(diff, diff) - dot2 * (dot2 + 4 * parab->k);
	poly.disc = SQUARE(poly.b) - 4 * poly.a * poly.c;
	if (poly.disc < 0)
		return (-1);
	return (resolve_poly2(poly));
}
