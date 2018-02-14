/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:51:30 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/14 13:49:44 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec4	dmult_vec4(t_vec4 u, double n)
{
	u.x *= n;
	u.y *= n;
	u.z *= n;
	return (u);
}

t_vec3	dmult_vec3(t_vec3 u, double n)
{
	u.x *= n;
	u.y *= n;
	u.z *= n;
	return (u);
}

t_vec3	mult_vec3(t_vec3 u, t_vec3 v)
{
	u.x *= v.x;
	u.y *= v.y;
	u.z *= v.z;
	return (u);
}

double	dot_vec4(t_vec4 u, t_vec4 v)
{
	return(u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w);
}

double	dot_vec3(t_vec3 u, t_vec3 v)
{
	return(u.x * v.x + u.y * v.y + u.z * v.z);
}
