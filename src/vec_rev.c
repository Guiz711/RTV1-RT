/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_rev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:58:22 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/22 11:04:55 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec2	rev_vec2(t_vec2 u)
{
	u.x = -u.x;
	u.y = -u.y;
	return (u);
}

t_vec3	rev_vec3(t_vec3 u)
{
	u.x = -u.x;
	u.y = -u.y;
	u.z = -u.z;
	return (u);
}

t_vec4	rev_vec4(t_vec4 u)
{
	u.x = -u.x;
	u.y = -u.y;
	u.z = -u.z;
	return (u);
}
