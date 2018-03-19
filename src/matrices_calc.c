/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_calc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 19:49:02 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 19:49:05 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/*
** transforms a point by a matrix
*/

t_vec4	new_coord(t_vec4 p, t_mtx4 mtx)
{
	double	tmp[4];

	tmp[0] = p.x * mtx.a[0] + p.y * mtx.a[1] + p.z * mtx.a[2] + p.w * mtx.a[3];
	tmp[1] = p.x * mtx.b[0] + p.y * mtx.b[1] + p.z * mtx.b[2] + p.w * mtx.b[3];
	tmp[2] = p.x * mtx.c[0] + p.y * mtx.c[1] + p.z * mtx.c[2] + p.w * mtx.c[3];
	tmp[3] = p.x * mtx.d[0] + p.y * mtx.d[1] + p.z * mtx.d[2] + p.w * mtx.d[3];
	p.x = tmp[0];
	p.y = tmp[1];
	p.z = tmp[2];
	p.w = tmp[3];
	return (p);
}
