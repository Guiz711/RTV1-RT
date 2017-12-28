/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/28 13:43:34 by gmichaud         ###   ########.fr       */
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

/*void	init_scene(t_scene *scn)
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cyl;
	t_cone		cone;
	t_light		light;

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
	plane.p = ft_init_vec4(-20, 0, 0, 1);
	plane.normal = ft_normalize(ft_init_vec4(-1, 0, 0, 0));
	plane.color = ft_init_vec3(0.18, 0.18, 0.18);//0x00FFFFFF;
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	plane.p = ft_init_vec4(20, 0, 0, 1);
	plane.normal = ft_normalize(ft_init_vec4(1, 0, 0, 0));
	plane.color = ft_init_vec3(0.18, 0.18, 0.18);//0x00FFFFFF;
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	plane.p = ft_init_vec4(0, 20, 0, 1);
	plane.normal = ft_normalize(ft_init_vec4(0, 1, 0, 0));
	plane.color = ft_init_vec3(0.18, 0.18, 0.18);//0x00FFFFFF;
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	cyl.p = ft_init_vec4(-10, 0, -45, 1);
	cyl.dir = ft_init_vec4(0, 1, 0, 0);
	cyl.radius = 3;
	cyl.color = ft_init_vec3(0.18, 0.05, 0.05);//0x00FF0000;
	obj_lstadd(&(scn->objs), obj_lstnew(CYLINDER, &cyl, sizeof(cyl)));
	cone.p = ft_init_vec4(-2, 0, -40, 1);
	cone.dir = ft_init_vec4(-0.5, 1, 0, 0);
	cone.angle = 30;
	cone.ang_tan = 1 + SQUARE(tan(RAD(cone.angle * 0.5)));
	cone.color = ft_init_vec3(0, 0, 0.18); //0x000000FF;
	//obj_lstadd(&(scn->objs), obj_lstnew(CONE, &cone, sizeof(cone)));
	//scn->light.type = DIRECTIONNAL;
	//scn->light.vec = ft_normalize(ft_init_vec4(1, -0.7, -0.9, 0));
	//scn->light.intensity = 6;
	light.type = POINT;
	light.vec = ft_init_vec4(19.5, 0, -20, 1);
	light.intensity = 3000;
	light.color = ft_init_vec3(1, 1, 1); //0x00FFFFFF
	scn->light = ft_lstnew(&light, sizeof(light));
	light.type = POINT;
	light.vec = ft_init_vec4(-19.5, 0, -20, 1);
	light.intensity = 3000;
	light.color = ft_init_vec3(1, 1, 1); //0x00FFFFFF
	//scn->light = ft_lstnew(&light, sizeof(light));
	ft_lstadd(&(scn->light), ft_lstnew(&light, sizeof(light)));
	light.type = POINT;
	light.vec = ft_init_vec4(-19.5, 15, -75, 1);
	light.intensity = 3000;
	light.color = ft_init_vec3(1, 1, 1); //0x00FFFFFF
	//scn->light = ft_lstnew(&light, sizeof(light));
	ft_lstadd(&(scn->light), ft_lstnew(&light, sizeof(light)));
	light.type = POINT;
	light.vec = ft_init_vec4(19.5, 0, -75, 1);
	light.intensity = 3000;
	light.color = ft_init_vec3(1, 1, 1); //0x00FFFFFF
	//scn->light = ft_lstnew(&light, sizeof(light));
	ft_lstadd(&(scn->light), ft_lstnew(&light, sizeof(light)));
	scn->cam.orient = ft_init_vec4(0, 0, 1, 0);
	scn->cam.orig = ft_init_vec4(0, 0, -3, 1);
}*/

void	init_scene(t_scene *scn)
{
	t_sphere	sphere;
	t_plane		plane;
	t_light		light;
	t_obj_lst	*new;

	sphere.center = init_vec4(0, 0, -10, 1);
	sphere.radius = 2;
	scn->objs = obj_lstnew(SPHERE, &sphere, sizeof(sphere));
	scn->objs->material.model = PHONG;
	scn->objs->material.diff = init_vec3(0.05, 0.20, 0.05); //0x0000FFFF;
	scn->objs->material.amb = init_vec3(0.05, 0.20, 0.05); //0x0000FFFF;
	scn->objs->material.spec = init_vec3(0.05, 0.20, 0.05); //0x0000FFFF;
	scn->objs->material.shin = 80;

	plane.p = init_vec4(0, 0, -12, 1);
	plane.normal = normalize_vec4(init_vec4(0, 0, -1, 0));
	new = obj_lstnew(PLANE, &plane, sizeof(plane));
	new->material.model = LAMBERT;
	new->material.amb = init_vec3(0.18, 0.22, 0.26);//0x00FFFFFF;
	new->material.diff = init_vec3(0.18, 0.22, 0.26);//0x00FFFFFF;
	new->material.spec = init_vec3(0.18, 0.22, 0.26);//0x00FFFFFF;
	new->material.shin = 0;
	obj_lstadd(&(scn->objs), new);

	light.type = POINT;
	light.vec = init_vec4(-12.5, -5, 5, 1);
	//light.vec = normalize_vec4(init_vec4(1, -0.5, -0.5, 0));
	light.range = 1000;
	light.diff_i = init_vec3(1, 1, 1); //0x00FFFFFF
	light.spec_i = init_vec3(1, 1, 1); //0x00FFFFFF
	scn->light = ft_lstnew(&light, sizeof(light));

	/*light.type = POINT;
	light.vec = init_vec4(12.5, 0, 0, 1);
	light.intensity = 3000;
	light.color = init_vec3(1, 1, 1); //0x00FFFFFF*/

	scn->cam.orient = init_vec4(0, 0, 1, 0);
	scn->cam.orig = init_vec4(0, 0, -3, 1);
	scn->shd[FACING] = 1;
	scn->shd[NO_SHD] = 0;
}

/*void	put_pixel(int pos, t_img *img, unsigned int color)
{
	char	*data;
	int		width;
	int		inc;

	data = img->data;
	inc = img->color_depth / 8;
	width = img->width;
	ft_memcpy(&data[pos * inc], &color, sizeof(color));
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

t_vec3	lambert_lightning(t_vec3 albedo, t_ray *ray, t_light *light)
{
	t_vec4			dir;
	t_vec3			col;
	double			ratio;
	double			intensity;

	if (light->type == DIRECTIONNAL)
	{
		dir = rev_vec4(light->vec);
		intensity = light->intensity;
	}
	else
	{
		dir = rev_vec4(sub_vec4(ray->inter, light->vec));
		intensity = light->intensity / (4 * M_PI * norm_vec4(dir));
		dir = normalize_vec4(dir);
	}
	ratio = intensity * dot_vec4(ray->obj_normal, dir);
	col.z = albedo.z / M_PI * light->color.z * ratio;
	col.y = albedo.y / M_PI * light->color.y * ratio;
	col.x = albedo.x / M_PI * light->color.x * ratio;
	return (col);
}

int		shadowing(t_light light, t_ray *ray, t_args *args)
{
	t_ray		light_ray;
	t_obj_lst	*objs;
	double		inter;

	objs = args->scene->objs;
	if (light.type == DIRECTIONNAL)
	{
		light_ray.dir = rev_vec4(light.vec);
		light_ray.inter_dist = 1e6;
	}
	else
	{
		light_ray.dir = rev_vec4(sub_vec4(ray->inter, light.vec));;
		light_ray.inter_dist = norm_vec4(light_ray.dir);
		light_ray.dir = normalize_vec4(light_ray.dir);
	}
	light_ray.orig = init_vec4(ray->inter.x + ray->obj_normal.x * 0.000007,
		ray->inter.y + ray->obj_normal.y * 0.000007,
		ray->inter.z + ray->obj_normal.z * 0.000007, 1);
	while (objs)
	{
		inter = args->obj_fct[objs->content_type](light_ray, (void*)objs->content);
		if (inter > 0 && inter < light_ray.inter_dist)
			return (0);
		objs = objs->next;
	}
	return (1);	
}

void	phong_shading(t_ray *ray, t_light light)
{
	t_vec4	r;
	t_vec4	ldir;
	double	ndotl;

	ldir = rev_vec4(sub_vec4(ray->inter, light.vec));
	ldir = normalize_vec4(ldir);
	//ldir = ft_init_vec4(ray->inter.x - light.vec.x,
	//	ray->inter.y - light.vec.y, ray->inter.z - light.vec.z, 0);
	ndotl = 2 * dot_vec4(ray->obj_normal, ldir);
	r = sub_vec4(new_coord(ray->obj_normal, ft_scale(ndotl, ndotl, ndotl)), ldir);
	ft_init_vec4(ndotl * ray->obj_normal.x - ldir.x,
		ndotl * ray->obj_normal.y - ldir.y,
		ndotl * ray->obj_normal.z - ldir.z, 0);
	r = normalize_vec4(r);
	ray->col_ratio.x = ray->col_ratio.x
		+ (pow(dot_vec4(ray->obj_normal, r), ray->inter_obj->material.n)
		* ray->inter_obj->material.spec);
	ray->col_ratio.y = ray->col_ratio.y
		+ (pow(dot_vec4(ray->obj_normal, r), ray->inter_obj->material.n)
		* ray->inter_obj->material.spec);
	ray->col_ratio.z = ray->col_ratio.z
		+ (pow(dot_vec4(ray->obj_normal, r), ray->inter_obj->material.n)
		* ray->inter_obj->material.spec);
}

void	shade(t_args *args)
{
	size_t		i;
	t_ray		*rays;
	t_list		*light;
	t_vec3		part;
	uint32_t	hex_col;
	unsigned	char *comp;

	rays = args->ray_buf;
	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT)
	{
		light = args->scene->light;
		while (light)
		{
			if (shadowing(*(t_light*)light->content, &rays[i], args) && rays[i].inter_obj)
			{
				part = lambert_lightning(rays[i].color, &rays[i], (t_light*)light->content);
				rays[i].col_ratio.x += part.x;
				rays[i].col_ratio.y += part.y;
				rays[i].col_ratio.z += part.z;
				phong_shading(&rays[i], *(t_light*)light->content);
			}
			light = light->next;
		}
		rays[i].col_ratio.x += rays[i].color.x * 0.3;
		rays[i].col_ratio.y += rays[i].color.y * 0.3;
		rays[i].col_ratio.z += rays[i].color.z * 0.3;
		hex_col = 0;
		comp = (unsigned char*)&hex_col;
		comp[0] = fmax(fmin((int)(rays[i].col_ratio.z * 255), 255), 0);
		comp[1] = fmax(fmin((int)(rays[i].col_ratio.y * 255), 255), 0);
		comp[2] = fmax(fmin((int)(rays[i].col_ratio.x * 255), 255), 0);
		put_pixel(i, args->env->img, hex_col);
		++i;
	}
}*/

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

int		main(void)
{
	t_args	args;
	t_env	env;
	t_scene scene;
	t_pixel	*pix;
	//t_mtx4	v2w;

	env.win_height = WIN_HEIGHT;
	env.win_width = WIN_WIDTH;
	env.fov = FOVX;
	env.init = mlx_init();
	env.win = mlx_new_window(env.init, WIN_WIDTH, WIN_HEIGHT, "RTV1");
	init_img(&env);
	init_scene(&scene);
	args.obj_fct[0] = &sphere_intersection;
	args.obj_fct[1] = &plane_intersection;
	args.obj_fct[2] = &cylinder_intersection;
	args.obj_fct[3] = &cone_intersection;
	args.norm_fct[0] = &sphere_normal;
	args.norm_fct[1] = &plane_normal;
	args.norm_fct[2] = &cylinder_normal;
	args.norm_fct[3] = &cone_normal;
	args.shd_fct[NO_SHD] = &raw_color;
	args.shd_fct[FACING] = &facing_ratio;
	pix = create_ray_array(&env, ft_translate(0, 0, 0));
	//v2w = ft_mtx_mult(ft_translate(-7, -10, -5), ft_rotation('x', RAD(65)));
	//v2w = ft_mtx_mult(v2w, ft_rotation('x', RAD(-10)));
	//pix = create_ray_array(&env, ft_mtx_mult(v2w, ft_rotation('y', RAD(-40))));
	//ray_list = create_ray_array(ft_mtx_mult(ft_translate(0, -10, -5), ft_rotation('x', RAD(0))));
	args.env = &env;
	args.scene = &scene;
	args.pix_buf = pix;
	trace_primary_rays(&args);
	manage_shaders(&args);
	//fill_image(&args);
	mlx_put_image_to_window(env.init, env.win, env.img->ptr, 0, 0);
	mlx_loop(env.init);
	return (0);
}
