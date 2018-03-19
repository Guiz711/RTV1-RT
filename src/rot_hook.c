/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:51:11 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 12:50:09 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3				feed_rot(t_hook hook)
{
	t_vec3			rot;

	if (hook.rot_x == 1 || hook.rot_x == 0)
		rot.x = (hook.rot_x == 1 ? 0.1 : 0);
	else
		rot.x = -0.1;
	if (hook.rot_y == 1 || hook.rot_y == 0)
		rot.y = (hook.rot_y == 1 ? 0.1 : 0);
	else
		rot.y = -0.1;
	if (hook.rot_z == 1 || hook.rot_z == 0)
		rot.z = (hook.rot_z == 1 ? 0.1 : 0);
	else
		rot.z = -0.1;
	return (rot);
}

int					modif_rot_obj(t_args *args)
{
	t_vec3			trans_rot;
	t_obj_lst		*tmp;

	trans_rot = feed_rot(args->env->hook);
	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj && args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	if (args->scene->objs->content_type != 0)
		args->modif_rot[args->scene->objs->content_type](args, trans_rot);
	args->scene->objs = tmp;
	return (0);
}
