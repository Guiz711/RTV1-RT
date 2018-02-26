/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 01:50:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/26 12:30:15 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			check_hook(t_args *args)
{
	if (args->env->hook.left_right == 1)
		args->scene->cam.orig.x -= 0.1;
	if (args->env->hook.left_right == -1)
		args->scene->cam.orig.x += 0.1;
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
	if (args->env->hook.trans_x != 0 || args->env->hook.trans_y != 0 || args->env->hook.trans_z != 0)
		modif_trans_obj(args);
	if (args->env->hook.rot_x != 0 || args->env->hook.rot_y != 0 || args->env->hook.rot_z != 0)
		modif_rot_obj(args);

	return (0);
}

void		trans_ori_cam(t_args *args, int keycode)
{
	if (keycode == LEFT)
		args->scene->cam.orig.x -= 0.5;
	if (keycode == RIGHT)
		args->scene->cam.orig.x += 0.5;
	if (keycode == UP)
		args->scene->cam.orig.z -= 0.5;
	if (keycode == BACK)
		args->scene->cam.orig.z += 0.5;
	if (keycode == 78)
		args->scene->cam.orig.y += 0.5;
	if (keycode == 69)
		args->scene->cam.orig.y -= 0.5;
}


int			hook(int keycode, t_args *args)
{
	if (keycode == KEY_ESC)
		quit((t_args*)args);
	else if (keycode == KEY_I)
		redraw(args);
	else if (keycode == KEY_DIVIDE || keycode == KEY_MULTIPLY)
	{
		if (set_aliasing(keycode, args) == 1)
		{
			free(args->pix_buf);
			args->pix_buf = init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
			manage_threads(args);
		}
	}
	if (keycode == 257)
	{
		if (args->env->moving == 1)
		{
			args->env->aliasing = 1;
			args->env->thread_number = THREADS_NUMBER;
			args->scene->render_mode = args->env->rendertmp;
			args->env->moving = 0;
			free(args->pix_buf);
			args->pix_buf = init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
			manage_threads(args);
		}
		else
		{
			args->env->aliasing = 14;
			args->env->thread_number = 1;
			args->env->rendertmp = args->scene->render_mode;
			args->env->moving = 1;
		}
	}
	if (args->env->moving == 1)
	{
		if (keycode == LEFT || keycode == RIGHT)
			args->env->hook.left_right = (keycode == LEFT ? 1 : -1);
		if (keycode == UP || keycode == DOWN)
			args->env->hook.up_down = (keycode == UP ? 1 : -1);
		if ( keycode == FORWARD | keycode == BACK)
			args->env->hook.backforw = (keycode == FORWARD ? 1 : -1);
		if ((keycode == C_SCALE || keycode == V_SCALE) && args->env->sel_obj != 0)
			args->env->hook.scale = (keycode == C_SCALE ? 1 : -1);
		if ((keycode == Q_TRANSX || keycode == A_TRANSX) && args->env->sel_obj != 0)
			args->env->hook.trans_x = (keycode == Q_TRANSX ? 1 : -1);
		if ((keycode == W_TRANSY || keycode == S_TRANSY) && args->env->sel_obj != 0)
			args->env->hook.trans_y = (keycode == W_TRANSY ? 1 : -1);
		if ((keycode == E_TRANSZ || keycode == D_TRANSZ) && args->env->sel_obj != 0)
			args->env->hook.trans_z = (keycode == E_TRANSZ ? 1 : -1);
		if ((keycode == R_ROTX || keycode == F_ROTX) && args->env->sel_obj != 0)
			args->env->hook.rot_x = (keycode == R_ROTX ? 1 : -1);
		if ((keycode == T_ROTY || keycode == G_ROTY) && args->env->sel_obj != 0)
			args->env->hook.rot_y = (keycode == T_ROTY ? 1 : -1);
		if ((keycode == Y_ROTZ || keycode == H_ROTZ) && args->env->sel_obj != 0)
			args->env->hook.rot_z = (keycode == Y_ROTZ ? 1 : -1);
		if (keycode == KEY_DIVIDE || keycode == KEY_MULTIPLY)
			args->env->aliasing = set_aliasing(keycode, args);
		free(args->pix_buf);
		args->pix_buf = init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
		manage_threads(args);
	}
	return (0);
}

int			select_obj(int button, int x, int y, t_args *args)
{
	t_inter	inter;
	size_t	pos;

	if (button == 1 && args->env->moving == 0)
	{
		y = (y < 0 ? y * -1 : y);
		pos = y * args->env->win_width + x;
		inter = trace_ray(args->pix_buf[pos].p_ray, args->scene->objs, args->obj_fct, 0);
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

int			modif_scale_obj(t_args *args)
{
	t_sphere		*sphere;
	t_cone			*cone;
	t_cylinder		*cyl;
	t_obj_lst		*tmp;

	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj && args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	if (args->scene->objs->content_type == SPHERE)
	{
		sphere = (t_sphere*)args->scene->objs->content;
		sphere->radius = (args->env->hook.scale == 1 ? sphere->radius * 1.1 : sphere->radius / 1.1) ;
		args->scene->objs->content = sphere;
	}
	else if (args->scene->objs->content_type == CONE)
	{
		cone = (t_cone*)args->scene->objs->content;
		cone->angle = (args->env->hook.scale == 1 ? cone->angle * 1.1 : cone->angle / 1.1) ;
		;
		args->scene->objs->content = cone;
	}
	else if (args->scene->objs->content_type == CYLINDER)
	{
		cyl = (t_cylinder*)args->scene->objs->content;
		cyl->radius =  (args->env->hook.scale == 1 ? cyl->radius * 1.5 : cyl->radius / 1.5) ;
		args->scene->objs->content = cyl;
	}
	args->scene->objs = tmp;
	return (0);
}

t_vec3			feed_trans2(t_hook hook)
{
	t_vec3		pos;

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
	return(pos);
}

int			modif_trans_obj(t_args *args)
{
	t_sphere		*sphere;
	t_plane			*plan;
	t_cone			*cone;
	t_cylinder		*cyl;
	t_vec3			trans_pos;
	t_obj_lst		*tmp;

	trans_pos = feed_trans2(args->env->hook);
	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj && args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	if (args->scene->objs->content_type == PLANE)
	{
		plan = (t_plane*)args->scene->objs->content;
		plan->p =  new_coord(plan->p, translate(trans_pos.x, trans_pos.y, trans_pos.z));
		args->scene->objs->content = plan;
	}
	else if (args->scene->objs->content_type == CONE)
	{
		cone = (t_cone*)args->scene->objs->content;
		cone->p =  new_coord(cone->p, translate(trans_pos.x, trans_pos.y, trans_pos.z));
		args->scene->objs->content = cone;
	}
	else if (args->scene->objs->content_type == CYLINDER)
	{
		cyl = (t_cylinder*)args->scene->objs->content;
		cyl->p =  new_coord(cyl->p, translate(trans_pos.x, trans_pos.y, trans_pos.z));
		args->scene->objs->content = cyl;
	}
	else if (args->scene->objs->content_type == SPHERE)
	{
		sphere = (t_sphere*)args->scene->objs->content;
		sphere->center =  new_coord(sphere->center, translate(trans_pos.x, trans_pos.y, trans_pos.z));
		args->scene->objs->content = sphere;
	}

	args->scene->objs = tmp;
	return (0);
}

t_vec3			feed_rot(t_hook hook)
{
	t_vec3		rot;

	if (hook.rot_x == 1 || hook.rot_x == 0)
			rot.x = (hook.rot_x == 1 ? 1 : 0);
	else
		rot.x = -1;
	if (hook.rot_y == 1 || hook.rot_y == 0)
			rot.y = (hook.rot_y == 1 ? 1 : 0);
	else
		rot.y = -1;
	if (hook.rot_z == 1 || hook.rot_z == 0)
			rot.z = (hook.rot_z == 1 ? 1 : 0);
	else
		rot.z = -1;
	return(rot);
}

int			modif_rot_obj(t_args *args)
{
	t_plane			*plan;
	t_cone			*cone;
	t_cylinder		*cyl;
	t_vec3			trans_rot;
	t_obj_lst		*tmp;

	trans_rot = feed_rot(args->env->hook);
	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj && args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	if (args->scene->objs->content_type == PLANE)
	{
		plan = (t_plane*)args->scene->objs->content;
		plan->normal =  new_coord(plan->normal, quat_to_mtx(euler_to_quat(trans_rot)));
		args->scene->objs->content = plan;
	}
	else if (args->scene->objs->content_type == CONE)
	{
		cone = (t_cone*)args->scene->objs->content;
		cone->dir =  new_coord(cone->dir, quat_to_mtx(euler_to_quat(trans_rot)));
		args->scene->objs->content = cone;
	}
	else if (args->scene->objs->content_type == CYLINDER)
	{
		cyl = (t_cylinder*)args->scene->objs->content;
		cyl->dir =  new_coord(cyl->dir, quat_to_mtx(euler_to_quat(trans_rot)));
		args->scene->objs->content = cyl;
	}
	args->scene->objs = tmp;
	return (0);
}
