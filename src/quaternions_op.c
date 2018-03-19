/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:44:36 by gmichaud          #+#    #+#             */
/*   Updated: 2018/01/30 11:47:26 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

double	norm_quat(t_vec4 q)
{
	double norm;

	norm = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	return (norm);
}

t_vec4	normalize_quat(t_vec4 q)
{
	double	norm;

	norm = norm_vec4(q);
	if (norm)
	{
		q.x = q.x / norm;
		q.y = q.y / norm;
		q.z = q.z / norm;
	}
	else
	{
		q.x = 0;
		q.y = 0;
		q.z = 0;
	}
	q.w = 0;
	return (q);
}

t_vec4	mult_quat(t_vec4 q1, t_vec4 q2)
{
	t_vec4	qr;

	qr.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	qr.y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z;
	qr.z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
	qr.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (qr);
}
