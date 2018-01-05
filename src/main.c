/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2018/01/05 13:50:15 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*static void		events(void *args)
{
	t_env	*env;

	env = ((t_args*)args)->env;
	mlx_hook(env->win, 17, 0L, &quit, args);
	mlx_hook(env->win, KeyPress, KeyPressMask, &keypress, args);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, &keyrelease, args);
	mlx_loop_hook(env->init, &loop, args);
	mlx_loop(env->init);
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_args	args;
	t_view	v;
	int		err_type;

	if ((argc == 3 && ft_strcmp("print", argv[2])) || argc < 2 || argc > 3)
		error(NULL, ERR_ARGS);
	if ((err_type = init_args(&args, &env, &v)))
		error(&args, err_type);
	if ((err_type = init_map(&args, argv[1])))
		error(&args, err_type);
	if (argc == 3)
		print_map(args.map);
	events(&args);
	return (0);
}*/

void	init_scene(t_scene *scn)
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cyl;
	t_cone		cone;
	t_light		light;
	t_obj_lst	*new;

	sphere.center = init_vec4(0, 5, -10, 1);
	sphere.radius = 2;
	scn->objs = obj_lstnew(SPHERE, &sphere, sizeof(sphere));
	scn->objs->material.model = PHONG;
	scn->objs->material.diff = init_vec3(0.2, 0.8, 0.2); //0x0000FFFF;
	scn->objs->material.amb = init_vec3(0.2, 0.8, 0.2); //0x0000FFFF;
	scn->objs->material.spec = init_vec3(1, 1, 1); //0x0000FFFF;
	scn->objs->material.shin = 80;

	plane.p = init_vec4(0, 0, -20, 1);
	plane.normal = normalize_vec4(init_vec4(0, 0, 1, 0));
	new = obj_lstnew(PLANE, &plane, sizeof(plane));
	new->material.model = PHONG;
	new->material.amb = init_vec3(0.5, 0.5, 0.8);//0x00FFFFFF;
	new->material.diff = init_vec3(0.5, 0.5, 0.8);//0x00FFFFFF;
	new->material.spec = init_vec3(1, 1, 1);//0x00FFFFFF;
	new->material.shin = 50;
	obj_lstadd(&(scn->objs), new);

	cyl.p = init_vec4(-15, 0, -10, 1);
	cyl.dir = init_vec4(0, 1, 0, 0);
	cyl.radius = 2;
	new = obj_lstnew(CYLINDER, &cyl, sizeof(cyl));
	new->material.model = PHONG;
	new->material.amb = init_vec3(0.2, 0.2, 0.8);//0x00FFFFFF;
	new->material.diff = init_vec3(0.2, 0.2, 0.8);//0x00FFFFFF;
	new->material.spec = init_vec3(0.05, 0.05, 0.05);//0x00FFFFFF;
	new->material.shin = 1;
	obj_lstadd(&(scn->objs), new);

	cyl.p = init_vec4(15, 0, -10, 1);
	cyl.dir = init_vec4(0, 1, 0, 0);
	cyl.radius = 0.5;
	new = obj_lstnew(CYLINDER, &cyl, sizeof(cyl));
	new->material.model = PHONG;
	new->material.amb = init_vec3(0.9, 0.6, 0.05);//0x00FFFFFF;
	new->material.diff = init_vec3(0.9, 0.6, 0.05);//0x00FFFFFF;
	new->material.spec = init_vec3(0.2, 0.2, 0.2);//0x00FFFFFF;
	new->material.shin = 10;
	//obj_lstadd(&(scn->objs), new);

	cone.p = init_vec4(15, 0, -10, 1);
	cone.dir = init_vec4(0, 1, 0, 0);
	cone.angle = 45;
	cone.ang_tan = 1 + SQUARE(tan(RAD(cone.angle * 0.5)));
	new = obj_lstnew(CONE, &cone, sizeof(cone));
	new->material.model = PHONG;
	new->material.amb = init_vec3(0.9, 0.6, 0.05);//0x00FFFFFF;
	new->material.diff = init_vec3(0.9, 0.6, 0.05);//0x00FFFFFF;
	new->material.spec = init_vec3(0.5, 0.5, 0.5);//0x00FFFFFF;
	new->material.shin = 10;
	obj_lstadd(&(scn->objs), new);

	light.type = POINT;
	light.vec = init_vec4(-20, 0, 20, 1);
	//light.vec = normalize_vec4(init_vec4(1, -0.5, -0.5, 0));
	light.range = 3000;
	light.diff_i = init_vec3(10, 10, 10); //0x00FFFFFF
	light.spec_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF
	light.atten = init_vec3(0.0005, 0.0005, 1);
	scn->light = ft_lstnew(&light, sizeof(light));

	light.type = POINT;
	light.vec = init_vec4(-20.3, 0, 20, 1);
	light.range = 3000;
	light.diff_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF*/
	light.spec_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF*/
	light.atten = init_vec3(0.0005, 0.0005, 1);
	ft_lstadd(&scn->light, ft_lstnew(&light, sizeof(light)));

		light.type = POINT;
	light.vec = init_vec4(-20.3, 0, 20, 1);
	light.range = 3000;
	light.diff_i = init_vec3(1, 1, 1); //0x00FFFFFF*/
	light.spec_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF*/
	light.atten = init_vec3(0.0005, 0.0005, 1);
	ft_lstadd(&scn->light, ft_lstnew(&light, sizeof(light)));

	light.type = POINT;
	light.vec = init_vec4(-20, -0.3, 20, 1);
	light.range = 3000;
	light.diff_i = init_vec3(0.6, 0.6, 0.6); //0x00FFFFFF*/
	light.spec_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF*/
	light.atten = init_vec3(0.0005, 0.0005, 1);
	ft_lstadd(&scn->light, ft_lstnew(&light, sizeof(light)));

	light.type = POINT;
	light.vec = init_vec4(-20.3, -0.3, 20, 1);
	light.range = 3000;
	light.diff_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF*/
	light.spec_i = init_vec3(0.2, 0.2, 0.2); //0x00FFFFFF*/
	light.atten = init_vec3(0.0005, 0.0005, 1);
	//ft_lstadd(&scn->light, ft_lstnew(&light, sizeof(light)));

	scn->cam.orient = init_vec4(0, 0, 1, 0);
	scn->cam.orig = init_vec4(0, 0, -3, 1);
	scn->amb_i = init_vec3(0.15, 0.15, 0.15);
	scn->render_mode = 2;
	scn->shd[FACING] = 0;
	scn->shd[NO_SHD] = 1;
	scn->shd[LAMBERT] = 0;
	scn->shd[PHONG] = 0;
	scn->shd[SHADOW] = 0;
}

int		init_img(t_env	*env)
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

int		init_env(t_env *env)
{
	env->win_height = WIN_HEIGHT;
	env->win_width = WIN_WIDTH;
	env->fov = FOVX;
	if (!(env->init = mlx_init()))
		return (FAILURE);
	if (!(env->win = mlx_new_window(env->init, env->win_width,
		env->win_height, "RTV1")))
		return (FAILURE);
	if (!init_img(env))
		return (FAILURE);
	return (SUCCESS);
}

void	init_fct_arr(t_args *args)
{
	args->obj_fct[0] = &sphere_intersection;
	args->obj_fct[1] = &plane_intersection;
	args->obj_fct[2] = &cylinder_intersection;
	args->obj_fct[3] = &cone_intersection;
	args->norm_fct[0] = &sphere_normal;
	args->norm_fct[1] = &plane_normal;
	args->norm_fct[2] = &cylinder_normal;
	args->norm_fct[3] = &cone_normal;
	args->rdr_fct[0] = &render_mode_0;
	args->rdr_fct[1] = &render_mode_1;
	args->rdr_fct[2] = &render_mode_2;
	//args->shd_fct[LAMBERT] = &lambert_model;
	//args->shd_fct[PHONG] = &phong_model;
}

int		init_args(t_args *args, t_env *env, t_scene *scene)
{
	init_env(env);
	init_scene(scene);
	init_fct_arr(args);
	args->env = env;
	args->scene = scene;
	args->pix_buf = init_pix_buffer(env, ft_translate(0, 0, 20));
	return (SUCCESS);
}

int		main(void)
{
	t_args	args;
	t_env	env;
	t_scene scene;

	init_args(&args, &env, &scene);
	trace_primary_rays(&args);
	//manage_shaders(&args);
	mlx_put_image_to_window(env.init, env.win, env.img->ptr, 0, 0);
	mlx_loop(env.init);
	return (0);
}
