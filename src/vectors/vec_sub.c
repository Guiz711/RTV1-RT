/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 11:44:30 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/22 11:45:54 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2	sub_vec2(t_vec2 u, t_vec2 v)
{
	t_vec2	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	return (res);
}

t_vec3	sub_vec3(t_vec3 u, t_vec3 v)
{
	t_vec3	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	res.z = u.z - v.z;
	return (res);
}

t_vec4	sub_vec4(t_vec4 u, t_vec4 v)
{
	t_vec4	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	res.z = u.z - v.z;
	res.w = 0;
	return (res);
}
