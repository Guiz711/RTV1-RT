/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/07 11:39:12 by gmichaud         ###   ########.fr       */
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

	sphere.center = ft_init_vec4(-13, 5, -40, 1);
	sphere.radius = 3;
	sphere.color = 0x00FF0000;
	scn->items = ft_lstnew(&sphere, sizeof(sphere));
	sphere.center = ft_init_vec4(-1, -2, -20, 1);
	sphere.radius = 3;
	sphere.color = 0x000000FF;
	ft_lstadd(&(scn->items), ft_lstnew(&sphere, sizeof(sphere)));
	sphere.center = ft_init_vec4(0, 0, -40, 1);
	sphere.radius = 3;
	sphere.color = 0x0000FF00;
	ft_lstadd(&(scn->items), ft_lstnew(&sphere, sizeof(sphere)));
	scn->cam.orient = ft_init_vec4(0, 0, 1, 0);
	scn->cam.orig = ft_init_vec4(0, 0, -3, 1);
}

double	get_distance(double a, double b, double c, double disc)
{
	double	res;
	double	dist_1;
	double	dist_2;

	if (disc == 0)
		return (-0.5 * b / a);
	else
	{
		res = (b > 0) ? -0.5 * (b + sqrt(disc)) : -0.5 * (b - sqrt(disc));
		dist_1 = res / a;
		dist_2 = c / res;
	}
	return ((dist_1 < dist_2) ? dist_1 : dist_2);
}

double	check_intersection(t_vec4 dir, t_vec4 orig, t_vec4 ctr, double radius)
{
	t_vec4	diff;
	double	a;
	double	b;
	double	c;
	double	disc;

	diff = ft_init_vec4(orig.x - ctr.x, orig.y - ctr.y, orig.z - ctr.z, 0);
	a = ft_dot_product(dir, dir);
	b = 2 * ft_dot_product(dir, diff);
	c = ft_dot_product(diff, diff) - radius * radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1);
	return (get_distance(a, b, c, disc));
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

double	check_intersections(t_ray ray, t_list **items)
{
	t_sphere		*sph;
	t_list			*mark;
	double			inter;
	double			final;

	final = 100000000000;
	mark = NULL;
	while (*items)
	{
		sph = (t_sphere*)(*items)->content;
		inter = check_intersection(ray.dir, ray.orig, sph->center, sph->radius);
		if (inter < final && inter != -1)
		{
			final = inter;
			mark = *items;
		}
		*items = (*items)->next;
	}
	*items = mark;
	return (final);
}

unsigned int	shade(unsigned int color, double f_ratio)
{
	unsigned char	*comp;

	comp = (unsigned char*)&color;
	comp[0] *= f_ratio;
	comp[1] *= f_ratio;
	comp[2] *= f_ratio;
	return color;
}

int		raytracing(t_ray *ray_list, t_scene scn, t_env *env)
{
	size_t		i;
	t_list		*obj;
	double		dist;
	t_sphere	*sph;	
	t_vec4		inter;
	t_vec4		normal;
	double		f_ratio;

	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		obj = scn.items;
		dist = check_intersections(ray_list[i], &obj);
		if (obj)
		{
			sph = (t_sphere*)obj->content;
			inter = ft_init_vec4(ray_list[i].orig.x + ray_list[i].dir.x * dist,
				ray_list[i].orig.y + ray_list[i].dir.y * dist,
				ray_list[i].orig.z + ray_list[i].dir.z * dist, 1);
			normal = ft_init_vec4(inter.x - sph->center.x,
				inter.y - sph->center.y, inter.z - sph->center.z, 0);
			normal = ft_normalize(normal);
			f_ratio = ft_dot_product(normal, ft_init_vec4(-ray_list[i].dir.x,
				-ray_list[i].dir.y, -ray_list[i].dir.z, 0));
			put_pixel(i, env->img, shade(((t_sphere*)obj->content)->color, f_ratio));
		}
		++i;
	}
	return (0);
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

int		main(void)
{
	t_env	env;
	t_scene scene;
	t_ray	*ray_list;
	//t_mtx4	v2w;

	env.init = mlx_init();
	env.win = mlx_new_window(env.init, WIN_WIDTH, WIN_HEIGHT, "RTV1");
	init_img(&env);
	init_scene(&scene);
	ray_list = create_ray_array(ft_translate(0, 0, 2));
	//v2w = ft_mtx_mult(ft_translate(20, -5, 20), ft_rotation('y', RAD(30)));
	//ray_list = create_ray_array(ft_mtx_mult(v2w, ft_rotation('x', RAD(3))));
	raytracing(ray_list, scene, &env);
	mlx_put_image_to_window(env.init, env.win, env.img->ptr, 0, 0);
	mlx_loop(env.init);
	return (0);
}
