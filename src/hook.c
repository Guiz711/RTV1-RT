/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 01:50:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/15 04:14:10 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		trans_ori_cam(t_args *args, int keycode)
{
	if (keycode == LEFT)
		args->scene->cam.orig.x -= 1;
	if (keycode == RIGHT)
		args->scene->cam.orig.x += 1;
	if (keycode == UP)
		args->scene->cam.orig.z -= 1;
	 if (keycode == BACK)
		args->scene->cam.orig.z += 1;
	 if (keycode == 78)
		 args->scene->cam.orig.y += 1;
	 if (keycode == 69)
		 args->scene->cam.orig.y -= 1;
}

int			move_cam(int keycode, t_args *args)
{
	if (keycode == LEFT || keycode == RIGHT || keycode == UP || keycode == BACK | keycode == 78 | keycode == 69)
		trans_ori_cam(args, keycode);
	else
			return (0);
	//mlx_destroy_image(args->env->init, args->env->win);
	args->pix_buf = init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
	manage_threads(args);
	return (0);
}
