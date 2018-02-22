/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:20:56 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/22 09:30:45 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	norm_vec4(t_vec4 v)
{
	double norm;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (norm);
}

t_vec4	normalize_vec4(t_vec4 v)
{
	double	norm;

	norm = norm_vec4(v);
	if (norm)
	{
		v.x = v.x / norm;
		v.y = v.y / norm;
		v.z = v.z / norm;
	}
	else
	{
		v.x = 0;
		v.y = 0;
		v.z = 0;
	}
	v.w = 0;
	return (v);
}

t_vec4	cross_vec4(t_vec4 u, t_vec4 v)
{
	t_vec4 w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	w.w = 1;
	return (w);
}

t_vec4	cross_vec3(t_vec3 u, t_vec3 v)
{
	t_vec4 w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	return (w);
}

t_vec4	mult_vec4(t_vec4 u, t_vec4 v)
{
	u.x *= v.x;
	u.y *= v.y;
	u.z *= v.z;
	u.w = 0;
	return (u);
}
