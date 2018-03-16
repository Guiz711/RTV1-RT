/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2018/03/16 13:08:17 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

t_mtx4		get_camera_to_world(t_view *view)
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

void	benchmark(int res, char *def)
{
	static struct timespec	start;
	struct timespec			finish;
	double					elapsed;

	if (!res)
		clock_gettime(CLOCK_MONOTONIC, &start);
	else
	{
		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		printf("%s : %f\n", def, elapsed);
	}
}

void	benchmark_total(int res, char *def)
{
	static struct timespec	start;
	struct timespec			finish;
	double					elapsed;

	if (!res)
		clock_gettime(CLOCK_MONOTONIC, &start);
	else
	{
		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		printf("%s : %f\n", def, elapsed);
	}
}

int		main(int argc, char **argv)
{
	t_args					args;
	t_env					env;
	t_scene					scene;
	t_obj_lst				*objs;

	scene.path = argv[1];
	benchmark_total(0, NULL);
	if (argc != 2)
	{
		ft_putstr("Usage: ./rtv1 docname\n");
		return (0);
	}
	benchmark(0, NULL);
	init_args(&args, &env, &scene, scene.path);
	if (!init_textures(&args))
		return (0);
	objs = scene.objs;
	benchmark(1, "init time");
	benchmark(0, NULL);
	manage_threads(&args);
	benchmark(1, "graphics calc time");
	benchmark(0, NULL);
	mlx_put_image_to_window(env.init, env.win, env.img->ptr, 0, 0);
	benchmark(1, "display time");
	benchmark_total(1, "total time");
	mlx_hook(env.win, 17, 0L, &quit, &args);
	mlx_mouse_hook(env.win, select_obj, &args);
	mlx_hook(env.win, 2, 0, hook, &args);
	mlx_loop(env.init);
	return (0);
}
