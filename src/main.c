/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/11 13:50:56 by gmichaud         ###   ########.fr       */
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

	sphere.center = ft_init_vec4(16, 15, -75, 1);
	sphere.radius = 3;
	sphere.color = ft_init_vec3(0.05, 0.18, 0.18); //0x0000FFFF;
	scn->objs = obj_lstnew(SPHERE, &sphere, sizeof(sphere));
	sphere.center = ft_init_vec4(12, -2, -45, 1);
	sphere.radius = 5;
	sphere.color = ft_init_vec3(0.18, 0.05, 0.05);//0x00FF0000;
	obj_lstadd(&(scn->objs), obj_lstnew(SPHERE, &sphere, sizeof(sphere)));
	sphere.center = ft_init_vec4(-5, 3, -30, 1);
	sphere.radius = 3;
	sphere.color = ft_init_vec3(0.05, 0.18, 0.05);//0x0000FF00;
	obj_lstadd(&(scn->objs), obj_lstnew(SPHERE, &sphere, sizeof(sphere)));
	plane.p = ft_init_vec4(0, -5, 0, 1);
	plane.normal = ft_normalize(ft_init_vec4(0, -1, 0, 0));
	plane.color = ft_init_vec3(0.18, 0.18, 0.18);//0x00FFFFFF;
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	plane.p = ft_init_vec4(0, 0, -80, 1);
	plane.normal = ft_normalize(ft_init_vec4(0, 0, -1, 0));
	plane.color = ft_init_vec3(0.18, 0.18, 0.18);//0x00FFFFFF;
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	cyl.p = ft_init_vec4(-10, 0, -45, 1);
	cyl.dir = ft_init_vec4(0, 1, 0, 0);
	cyl.radius = 3;
	cyl.color = ft_init_vec3(0.18, 0, 0);//0x00FF0000;
	obj_lstadd(&(scn->objs), obj_lstnew(CYLINDER, &cyl, sizeof(cyl)));
	cone.p = ft_init_vec4(-2, 0, -40, 1);
	cone.dir = ft_init_vec4(-0.5, 1, 0, 0);
	cone.angle = 30;
	cone.ang_tan = 1 + SQUARE(tan(RAD(cone.angle * 0.5)));
	cone.color = ft_init_vec3(0, 0, 0.18); //0x000000FF;
	//obj_lstadd(&(scn->objs), obj_lstnew(CONE, &cone, sizeof(cone)));
	//scn->light.type = DIRECTIONNAL;
	//scn->light.vec = ft_normalize(ft_init_vec4(1, -0.7, -0.9, 0));
	//scn->light.dir = ft_init_vec4(0, 0, -1, 0);
	scn->light.type = POINT;
	scn->light.vec = ft_init_vec4(-25, 10, -10, 1);
	scn->light.intensity = 6000;
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

unsigned int	lambert_lightning(t_vec3 albedo, t_ray ray, t_light light)
{
	uint32_t		hex_col;
	t_vec4			dir;
	float			ratio;
	unsigned char	*comp;

	hex_col = 0x00FFFFFF;
	comp = (unsigned char*)&hex_col;
	if (light.type == DIRECTIONNAL)
	{
		dir = ft_init_vec4(-light.vec.x, -light.vec.y, -light.vec.z, 0);
	}
	else
	{
		dir = ft_init_vec4(-(ray.inter.x - light.vec.x),
			-(ray.inter.y - light.vec.y), -(ray.inter.z - light.vec.z), 0);
		light.intensity = light.intensity / (4 * M_PI * ft_vec_norm(dir));
		dir = ft_normalize(dir);
	}
	ratio = light.intensity * ft_dot_product(ray.obj_normal, dir);
	comp[0] *= fmax(fmin(albedo.z / M_PI * light.color.z * ratio, 1), 0);
	comp[1] *= fmax(fmin(albedo.y / M_PI * light.color.y * ratio, 1), 0);
	comp[2] *= fmax(fmin(albedo.x / M_PI * light.color.x * ratio, 1), 0);
	return (hex_col);
}

unsigned int	shadowing(t_light light, t_ray *ray, t_args *args)
{
	t_ray		light_ray;
	t_obj_lst	*objs;
	double		inter;

	objs = args->scene->objs;
	if (light.type == DIRECTIONNAL)
	{
		light_ray.dir = ft_init_vec4(-light.vec.x,
			-light.vec.y, -light.vec.z, 0);
	}
	else
	{
		light_ray.dir = ft_init_vec4(-(ray->inter.x - light.vec.x),
			-(ray->inter.y - light.vec.y), -(ray->inter.z - light.vec.z), 0);
		light_ray.inter_dist = ft_vec_norm(light_ray.dir);
		light_ray.dir = ft_normalize(light_ray.dir);
	}
	light_ray.orig = ft_init_vec4(ray->inter.x, ray->inter.y, ray->inter.z, 1);
	light_ray.inter_dist = 1e6;
	while (objs)
	{
		inter = args->obj_fct[objs->content_type](light_ray, (void*)objs->content);
		if (inter > 0 || (light.type == POINT && inter < light_ray.inter_dist))
			return (0);
		objs = objs->next;
	}
	return (1);	
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
		hex_col = lambert_lightning(rays[i].color, rays[i], args->scene->light);
		hex_col *= shadowing(args->scene->light, &rays[i], args);
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
	//t_mtx4	v2w;

	env.init = mlx_init();
	env.win = mlx_new_window(env.init, WIN_WIDTH, WIN_HEIGHT, "RTV1");
	init_img(&env);
	init_scene(&scene);
	args.obj_fct[0] = &sphere_intersection;
	args.obj_fct[1] = &plane_intersection;
	args.obj_fct[2] = &cylinder_intersection;
	args.obj_fct[3] = &cone_intersection;
	ray_list = create_ray_array(ft_translate(0, 0, 2));
	//v2w = ft_mtx_mult(ft_translate(-20, 5, 0), ft_rotation('y', RAD(-45)));
	//ray_list = create_ray_array(ft_mtx_mult(v2w, ft_translate(-10, 0, 0)));
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
