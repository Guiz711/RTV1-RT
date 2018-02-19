/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:35:53 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/19 11:52:21 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec4	axisangle_to_quat(t_vec4 axis, double angle)
{
	t_vec4	qr;
	double	sin_a;

	sin_a = sin(angle / 2);
	qr.x = axis.x * sin_a;
	qr.y = axis.y * sin_a;
	qr.z = axis.z * sin_a;
	qr.w = cos(angle / 2);
	return (qr);
}

t_vec4	euler_to_quat(t_vec3 rot)
{
	t_vec4	x_quat;
	t_vec4	y_quat;
	t_vec4	z_quat;

	x_quat = axisangle_to_quat(init_vec4(1, 0, 0, 0), -rot.x);
	y_quat = axisangle_to_quat(init_vec4(0, 1, 0, 0), -rot.y);
	z_quat = axisangle_to_quat(init_vec4(0, 0, 1, 0), -rot.z);
	return (mult_quat(z_quat, mult_quat(x_quat, y_quat)));
}
