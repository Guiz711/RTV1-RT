/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 13:05:43 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/22 11:16:29 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/*
** The ft_init_vecx functions are initializing t_vec structs
** containing 2D, 3D or 4D vector coordinates.
** Returns an initialized vector type struct.
*/

t_vec2		init_vec2(float x, float y)
{
	t_vec2	vec2;

	vec2.x = x;
	vec2.y = y;
	return (vec2);
}

t_vec3		init_vec3(float x, float y, float z)
{
	t_vec3	vec3;

	vec3.x = x;
	vec3.y = y;
	vec3.z = z;
	return (vec3);
}

t_vec4		init_vec4(float x, float y, float z, float w)
{
	t_vec4	vec4;

	vec4.x = x;
	vec4.y = y;
	vec4.z = z;
	vec4.w = w;
	return (vec4);
}
