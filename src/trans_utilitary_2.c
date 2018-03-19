/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utilitary_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:47:04 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 16:22:45 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			trans_triangle(t_args *args, t_vec3 trans_pos)
{
	t_triangle	*triangle;

	triangle = (t_triangle*)args->scene->objs->content;
	triangle->p1 = new_coord(triangle->p1,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	triangle->p2 = new_coord(triangle->p2,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	triangle->p3 = new_coord(triangle->p3,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	args->scene->objs->content = triangle;
}
