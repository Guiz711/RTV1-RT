/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 01:50:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 20:42:56 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		trans_ori_cam(t_args *args, int keycode)
{
	t_vec3	rot;

	rot.y = 0;
	rot.z = 0;
	printf("???\n");
	if (keycode == LEFT)
	{
		rot.x = 10000;
		args->scene->cam.orient = new_coord(args->scene->cam.orient,
				quat_to_mtx(euler_to_quat(rot)));
		printf("helpp\n");
	}
	if (keycode == RIGHT)
	{
		rot.x = -10000;
		args->scene->cam.orient = new_coord(args->scene->cam.orient,
				quat_to_mtx(euler_to_quat(rot)));
		printf("why\n");
	}
	if (keycode == UP)
		args->scene->cam.orig.z -= 0.5;
	if (keycode == BACK)
		args->scene->cam.orig.z += 0.5;
	if (keycode == 78)
		args->scene->cam.orig.y += 0.5;
	if (keycode == 69)
		args->scene->cam.orig.y -= 0.5;
}

void		redraw(t_args *args)
{
	free(args->pix_buf);
	args->pix_buf =
		init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
	manage_threads(args);
}

void		moving(int keycode, t_args *args)
{
	if (keycode == LEFT || keycode == RIGHT)
		args->env->hook.left_right = (keycode == LEFT ? 1 : -1);
	if (keycode == UP || keycode == DOWN)
		args->env->hook.up_down = (keycode == UP ? 1 : -1);
	if (keycode == FORWARD | keycode == BACK)
		args->env->hook.backforw = (keycode == FORWARD ? 1 : -1);
	if ((keycode == C_SCALE || keycode == V_SCALE) && SEL != 0)
		args->env->hook.scale = (keycode == C_SCALE ? 1 : -1);
	if ((keycode == Q_TRANSX || keycode == A_TRANSX) && SEL != 0)
		args->env->hook.trans_x = (keycode == Q_TRANSX ? 1 : -1);
	if ((keycode == W_TRANSY || keycode == S_TRANSY) && SEL != 0)
		args->env->hook.trans_y = (keycode == W_TRANSY ? 1 : -1);
	if ((keycode == E_TRANSZ || keycode == D_TRANSZ) && SEL != 0)
		args->env->hook.trans_z = (keycode == E_TRANSZ ? 1 : -1);
	if ((keycode == R_ROTX || keycode == F_ROTX) && SEL != 0)
		args->env->hook.rot_x = (keycode == R_ROTX ? 1 : -1);
	if ((keycode == T_ROTY || keycode == G_ROTY) && SEL != 0)
		args->env->hook.rot_y = (keycode == T_ROTY ? 1 : -1);
	if ((keycode == Y_ROTZ || keycode == H_ROTZ) && SEL != 0)
		args->env->hook.rot_z = (keycode == Y_ROTZ ? 1 : -1);
	if (keycode == KEY_DIVIDE || keycode == KEY_MULTIPLY)
		args->env->aliasing = set_aliasing(keycode, args);
	redraw(args);
}

void		moving_mode(t_args *args)
{
	if (args->env->moving == 1)
	{
		args->env->aliasing = 1;
		args->env->thread_number = THREADS_NUMBER;
		args->scene->render_mode = args->env->rendertmp;
		args->env->moving = 0;
		redraw(args);
	}
	else
	{
		args->env->aliasing = 14;
		args->env->thread_number = 1;
		args->env->rendertmp = args->scene->render_mode;
		args->env->moving = 1;
	}
}

int			hook(int keycode, t_args *args)
{
	if (keycode == KEY_ESC)
		quit((t_args*)args);
	else if (keycode == KEY_DIVIDE || keycode == KEY_MULTIPLY)
	{
		if (set_aliasing(keycode, args) == 1)
			redraw(args);
	}
	if (keycode == 257)
		moving_mode(args);
	if (args->env->moving == 1)
		moving(keycode, args);
	return (0);
}
