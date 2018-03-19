/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:48:35 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 10:41:27 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

int		init_img(t_env *env)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (FAILURE);
	img->ptr = mlx_new_image(env->init, WIN_WIDTH, WIN_HEIGHT);
	img->endian = 0;
	img->width = WIN_WIDTH * COLOR_DEPTH / 8;
	img->height = WIN_HEIGHT;
	img->color_depth = COLOR_DEPTH / 8;
	img->data = mlx_get_data_addr(img->ptr, &img->color_depth,
		&img->width, &img->endian);
	env->img = img;
	return (SUCCESS);
}

int		init_hook(t_env *env)
{
	env->hook.up_down = 0;
	env->hook.backforw = 0;
	env->hook.left_right = 0;
	env->hook.scale = 0;
	env->hook.trans_x = 0;
	env->hook.trans_y = 0;
	env->hook.trans_z = 0;
	env->hook.rot_x = 0;
	env->hook.rot_y = 0;
	env->hook.rot_z = 0;
	return (0);
}

int		init_env(t_env *env)
{
	init_hook(env);
	env->thread_number = THREADS_NUMBER;
	env->moving = 0;
	env->sel_obj = 0;
	env->aliasing = 1;
	env->win_height = WIN_HEIGHT;
	env->win_width = WIN_WIDTH;
	env->fov = FOVX;
	if (!(env->init = mlx_init()))
		return (FAILURE);
	if (!(env->win = mlx_new_window(env->init, WIN_WIDTH,
		WIN_HEIGHT, "RTV1")))
		return (FAILURE);
	init_loadingscreen(env);
	if (!init_img(env))
		return (FAILURE);
	return (SUCCESS);
}

int		init_args(t_args *args, t_env *env, t_scene *scene, char *path)
{
	(void)path;
	init_env(env);
	scene->objs = NULL;
	scene->light = NULL;
	if (!xml_parse(path, scene))
		exit(-1);
	init_fct_arr(args);
	args->env = env;
	args->scene = scene;
	mlx_put_image_to_window(args->env->init, args->env->win,
			args->env->lodscreen->ptr, 0, 0);
	args->pix_buf = init_pix_buffer(env, get_camera_to_world(&scene->cam));
	return (SUCCESS);
}
