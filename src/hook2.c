/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:49:44 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 20:53:47 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			select_obj(int button, int x, int y, t_args *args)
{
	t_inter	inter;
	size_t	pos;

	if (button == 1 && args->env->moving == 0)
	{
		y = (y < 0 ? y * -1 : y);
		pos = y * args->env->win_width + x;
		inter = trace_ray(args->pix_buf[pos].p_ray,
				args->scene->objs, args->obj_fct, 0);
		if (inter.obj)
			args->env->sel_obj = inter.obj->id_obj;
		else
			args->env->sel_obj = 0;
		ft_putstr("Objet selectionne : ");
		ft_putnbr(args->env->sel_obj);
		ft_putstr("\n");
	}
	return (0);
}

int			check_hook(t_args *args)
{
	if (args->env->hook.left_right == 1)
		args->scene->cam.orient.y -= 1;
	if (args->env->hook.left_right == -1)
		args->scene->cam.orient.y += 1;
	if (args->env->hook.up_down == 1)
		args->scene->cam.orig.z -= 0.1;
	if (args->env->hook.up_down == -1)
		args->scene->cam.orig.z += 0.1;
	if (args->env->hook.backforw == 1)
		args->scene->cam.orig.y += 0.1;
	if (args->env->hook.backforw == -1)
		args->scene->cam.orig.y -= 0.1;
	if (args->env->hook.scale != 0)
		modif_scale_obj(args);
	if (args->env->hook.trans_x != 0 || args->env->hook.trans_y != 0
			|| args->env->hook.trans_z != 0)
		modif_trans_obj(args);
	if (args->env->hook.rot_x != 0 || args->env->hook.rot_y != 0
			|| args->env->hook.rot_z != 0)
		modif_rot_obj(args);
	return (0);
}
