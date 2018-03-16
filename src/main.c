/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:31:25 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/16 15:33:43 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

t_mtx4						get_camera_to_world(t_view *view)
{
	t_vec3					orient;
	t_mtx4					translation;
	t_mtx4					rotation;

	orient = init_vec3(RAD(view->orient.x),
		RAD(view->orient.y), RAD(view->orient.z));
	translation = translate(view->orig.x, view->orig.y, view->orig.z);
	rotation = quat_to_mtx(euler_to_quat(orient));
	return (mtx4_mult(translation, rotation));
}

int							main(int argc, char **argv)
{
	t_args					args;
	t_env					env;
	t_scene					scene;
	t_obj_lst				*objs;

	scene.path = argv[1];
	if (argc != 2)
	{
		ft_putstr("Usage: ./rtv1 docname\n");
		return (0);
	}
	init_args(&args, &env, &scene, scene.path);
	if (!init_textures(&args))
		return (0);
	objs = scene.objs;
	manage_threads(&args);
	mlx_put_image_to_window(env.init, env.win, env.img->ptr, 0, 0);
	mlx_hook(env.win, 17, 0L, &quit, &args);
	mlx_mouse_hook(env.win, select_obj, &args);
	mlx_hook(env.win, 2, 0, hook, &args);
	mlx_loop(env.init);
	return (0);
}
