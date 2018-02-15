/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 01:50:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/15 09:38:08 by jgourdin         ###   ########.fr       */
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
	else if ((keycode == 9 || keycode == 8) && args->env->sel_obj != 0)
		modif_scale_obj(keycode, args);
//	else if ((keycode == 126 || keycode == 125 || keycode == 124 || keycode == 123) && args->env->select_obj != 0)
//		modif_rot_obj(keycode, args);
	else
		return (0);
	//mlx_destroy_image(args->env->init, args->env->win);
	args->pix_buf = init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
	manage_threads(args);
	return (0);
}

int			select_obj(int button, int x, int y, t_args *args)
{
	t_inter	inter;
	size_t	pos;

	button = 0;
	pos = y * args->env->win_width + x;
	inter = trace_ray(args->pix_buf[pos].p_ray, args->scene->objs, args->obj_fct, 0);
	if (inter.obj)
		args->env->sel_obj = inter.obj->id_obj;
	else
		args->env->sel_obj = 0;
	ft_putstr("Objet selectionne : ");
	ft_putnbr(args->env->sel_obj);
	ft_putstr("\n");
	return (0);
}

int			modif_scale_obj(int keycode, t_args *args)
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
		sphere->radius = (keycode == 8 ? sphere->radius * 1.5 : sphere->radius / 1.5) ;
		args->scene->objs->content = sphere;
	}
	else if (args->scene->objs->content_type == CONE)
	{
		cone = (t_cone*)args->scene->objs->content;
		cone->angle = (keycode == 8 ? cone->angle * 1.5 : cone->angle / 1.5) ;
		;
		args->scene->objs->content = cone;
	}
	else if (args->scene->objs->content_type == CYLINDER)
	{
		cyl = (t_cylinder*)args->scene->objs->content;
		cyl->radius =  (keycode == 8 ? cyl->radius * 1.5 : cyl->radius / 1.5) ;
		args->scene->objs->content = cyl;
	}
	args->scene->objs = tmp;
	return (0);
}

/*int			modif_trans_obj(int keycode, t_args *args)
{
	t_plane			*plan;
	t_cone			*cone;
	t_cylinder		*cyl;
	t_obj_lst		*tmp;

	tmp = args->scene->objs;
	while (args->scene->objs->id_obj != args->env->sel_obj && args->scene->objs)
		args->scene->objs = args->scene->objs->next;
	if (args->scene->objs->content_type == PLANE)
	{
		plan = (t_plane*)args->scene->objs->content;
		plan->normal = (keycode == 8 ? plan->normal * 1.5 : sphere->radius / 1.5) ;
		args->scene->objs->content = sphere;
	}
	else if (args->scene->objs->content_type == CONE)
	{
		cone = (t_cone*)args->scene->objs->content;
		cone->angle = (keycode == 8 ? cone->angle * 1.5 : cone->angle / 1.5) ;
		;
		args->scene->objs->content = cone;
	}
	else if (args->scene->objs->content_type == CYLINDER)
	{
		cyl = (t_cylinder*)args->scene->objs->content;
		cyl->radius =  (keycode == 8 ? cyl->radius * 1.5 : cyl->radius / 1.5) ;
		args->scene->objs->content = cyl;
	}
	args->scene->objs = tmp;
	return (0);
}
*/
