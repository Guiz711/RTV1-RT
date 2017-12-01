/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 13:20:56 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/01 12:28:39 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	ft_vec_norm(t_vec4 v)
{
	float norm;

	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (norm);
}

t_vec4	ft_normalize(t_vec4 v)
{
	float	norm;

	norm = ft_vec_norm(v);
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

t_vec4	ft_cross_product(t_vec4 u, t_vec4 v)
{
	t_vec4 w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	w.w = 1;
	return (w);
}

double	ft_dot_product(t_vec4 u, t_vec4 v)
{
	return(u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w);
}
