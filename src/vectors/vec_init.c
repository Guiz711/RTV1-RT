/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:05:43 by gmichaud          #+#    #+#             */
/*   Updated: 2018/01/30 11:50:45 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/*
** The ft_init_vecx functions are initializing t_vec structs
** containing 2D, 3D or 4D vector coordinates.
** Returns an initialized vector type struct.
*/

t_vec2		init_vec2(double x, double y)
{
	t_vec2	vec2;

	vec2.x = x;
	vec2.y = y;
	return (vec2);
}

t_vec3		init_vec3(double x, double y, double z)
{
	t_vec3	vec3;

	vec3.x = x;
	vec3.y = y;
	vec3.z = z;
	return (vec3);
}

t_vec4		init_vec4(double x, double y, double z, double w)
{
	t_vec4	vec4;

	vec4.x = x;
	vec4.y = y;
	vec4.z = z;
	vec4.w = w;
	return (vec4);
}

t_vec3		vec4_to_vec3(t_vec4  v)
{
	return (init_vec3(v.x, v.y, v.z));
}