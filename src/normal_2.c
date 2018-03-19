/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:15:37 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 16:17:01 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec4	sphere_normal(t_ray *ray, t_inter *inter)
{
	t_sphere	*sph;
	t_vec4		normal;

	ray = NULL;
	sph = (t_sphere*)inter->obj->content;
	normal = normalize_vec4(sub_vec4(inter->p, sph->center));
	return (normal);
}
