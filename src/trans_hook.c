/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:46:01 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 18:06:08 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3				feed_trans2(t_hook hook)
{
	t_vec3			pos;

	if (hook.trans_x == 1 || hook.trans_x == 0)
		pos.x = (hook.trans_x == 1 ? 1 : 0);
	else
		pos.x = -1;
	if (hook.trans_y == 1 || hook.trans_y == 0)
		pos.y = (hook.trans_y == 1 ? 1 : 0);
	else
		pos.y = -1;
	if (hook.trans_z == 1 || hook.trans_z == 0)
		pos.z = (hook.trans_z == 1 ? 1 : 0);
	else
		pos.z = -1;
	return (pos);
}

int					modif_trans_obj(t_args *args)
{
	t_vec3			trans_pos;
	t_obj_lst		*tmp;

	trans_pos = feed_trans2(args->env->hook);
	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj && args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	args->modif_trans[args->scene->objs->content_type](args, trans_pos);
	args->scene->objs = tmp;
	return (0);
}
