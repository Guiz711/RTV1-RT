/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/10 10:58:23 by gmichaud         ###   ########.fr       */
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

	sphere.center = ft_init_vec4(-13, 3, -40, 1);
	sphere.radius = 3;
	sphere.color = ft_init_vec3(0, 0.18, 0.18); //0x0000FFFF;
	scn->objs = obj_lstnew(SPHERE, &sphere, sizeof(sphere));
	sphere.center = ft_init_vec4(12, -5, -45, 1);
	sphere.radius = 5;
	sphere.color = ft_init_vec3(0.18, 0, 0);//0x00FF0000;
	obj_lstadd(&(scn->objs), obj_lstnew(SPHERE, &sphere, sizeof(sphere)));
	sphere.center = ft_init_vec4(-5, 3, -30, 1);
	sphere.radius = 3;
	sphere.color = ft_init_vec3(0, 0.18, 0);//0x0000FF00;
	obj_lstadd(&(scn->objs), obj_lstnew(SPHERE, &sphere, sizeof(sphere)));
	plane.p = ft_init_vec4(0, -5, 0, 1);
	plane.normal = ft_normalize(ft_init_vec4(0, -1, 0, 0));
	plane.color = ft_init_vec3(0.18, 0.18, 0.18);//0x00FFFFFF;
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	cyl.p = ft_init_vec4(12, 0, -45, 1);
	cyl.dir = ft_init_vec4(0, 1, 0, 0);
	cyl.radius = 3;
	cyl.color = ft_init_vec3(0.18, 0, 0);//0x00FF0000;
	obj_lstadd(&(scn->objs), obj_lstnew(CYLINDER, &cyl, sizeof(cyl)));
	cone.p = ft_init_vec4(-2, 0, -40, 1);
	cone.dir = ft_init_vec4(-0.5, 1, 0, 0);
	cone.angle = 30;
	cone.ang_tan = 1 + SQUARE(tan(RAD(cone.angle * 0.5)));
	cone.color = ft_init_vec3(0, 0, 0.18); //0x000000FF;
	obj_lstadd(&(scn->objs), obj_lstnew(CONE, &cone, sizeof(cone)));
	scn->light.dir = ft_init_vec4(1, -0.3, 0, 0);
	scn->light.intensity = 3000;
	scn->light.color = ft_init_vec3(1, 1, 1); //0x00FFFFFF
	scn->cam.orient = ft_init_vec4(0, 0, 1, 0);
	scn->cam.orig = ft_init_vec4(0, 0, -3, 1);
}

void	put_pixel(int pos, t_img *img, unsigned int color)
{
	char	*data;
	int		width;
	int		inc;

	data = img->data;
	inc = img->color_depth / 8;
	width = img->width; //* (COLOR_DEPTH / 8);
	ft_memcpy(&data[pos * inc], &color, sizeof(color));
	//if (pos.x < (width / inc) && pos.y < img->height && pos.x >= 0
		//&& pos.y >= 0)
	//{
			//ft_memcpy(&data[((int)pos.y * width) + ((int)pos.x * inc)], &color,
				//sizeof(color));
	//}
}

unsigned int	facing_ratio(unsigned int color, double ratio)
{
	unsigned char	*comp;

	comp = (unsigned char*)&color;
	comp[0] *= ratio;
	comp[1] *= ratio;
	comp[2] *= ratio;
	return color;
}

unsigned int	lambert_lightning(t_vec3 albedo, t_vec4 normal, t_light light)
{
	uint32_t		hex_col;
	t_vec4			light_inv;
	float			ratio;
	unsigned char	*comp;

	hex_col = 0x00FFFFFF;
	comp = (unsigned char*)&hex_col;
	light_inv = ft_init_vec4(-light.dir.x, -light.dir.y, -light.dir.z, 0);
	ratio = light.intensity * ft_dot_product(normal, light_inv);
	if (ratio < 0)
		ratio = 0;
	comp[0] = albedo.z / M_PI * light.color.z * ratio;
	comp[1] = albedo.y / M_PI * light.color.y * ratio;
	comp[2] = albedo.x / M_PI * light.color.x * ratio;
	return (hex_col);
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
	return (1);
}

void	shade(t_args *args)
{
	size_t		i;
	//double		ratio;
	t_ray		*rays;
	uint32_t	hex_col;

	rays = args->ray_buf;
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		//ratio = ft_dot_product(rays[i].obj_normal, ft_init_vec4(-rays[i].dir.x,
			//-rays[i].dir.y, -rays[i].dir.z, 0));
		//if (rays[i].inter_obj && rays[i].inter_obj->content_type == PLANE)
			//ratio = -ratio;
		//hex_col = facing_ratio(rays[i].color, ratio);
		hex_col = lambert_lightning(rays[i].color, rays[i].obj_normal, args->scene->light);
		put_pixel(i, args->env->img, hex_col);
		++i;
	}
}

int		main(void)
{
	t_args	args;
	t_env	env;
	t_scene scene;
	t_ray	*ray_list;
	t_mtx4	v2w;

	env.init = mlx_init();
	env.win = mlx_new_window(env.init, WIN_WIDTH, WIN_HEIGHT, "RTV1");
	init_img(&env);
	init_scene(&scene);
	args.obj_fct[0] = &sphere_intersection;
	args.obj_fct[1] = &plane_intersection;
	args.obj_fct[2] = &cylinder_intersection;
	args.obj_fct[3] = &cone_intersection;
	//ray_list = create_ray_array(ft_translate(0, 0, 2));
	v2w = ft_mtx_mult(ft_translate(-20, 5, 0), ft_rotation('y', RAD(-45)));
	ray_list = create_ray_array(ft_mtx_mult(v2w, ft_translate(-10, 0, 0)));
	//ray_list = create_ray_array(ft_mtx_mult(ft_translate(0, 10, 2), ft_rotation('x', RAD(-10))));
	args.env = &env;
	args.scene = &scene;
	args.ray_buf = ray_list;
	raytracing(&args);
	shade(&args);
	//fill_image(&args);
	mlx_put_image_to_window(env.init, env.win, env.img->ptr, 0, 0);
	mlx_loop(env.init);
	return (0);
}
