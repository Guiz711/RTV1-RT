/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/04 13:37:12 by gmichaud         ###   ########.fr       */
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

	sphere.center = ft_init_vec4(0, 0, 0, 1);
	sphere.radius = 1;
	sphere.color = 0x00FF0000;
	scn->items = ft_lstnew(&sphere, sizeof(sphere));
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

int		check_intersections(t_ray ray, t_scene scn)
{
	t_sphere	*sph;
	double		inter;
	double		final;

	final = 0;
	while (scn.items)
	{
		sph = (t_sphere*)scn.items->content;
		inter = check_intersection(ray.dir, ray.orig, sph->center, sph->radius);
		if (final == 0 || inter < final)
			final = inter;
		scn.items = scn.items->next;
	}
	printf("%f ; ", final);
	if (final)
		return (TRUE);
	return (FALSE);
}

int		raytracing(t_ray *ray_list, t_scene scn)
{
	size_t	i;

	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		check_intersections(ray_list[i], scn);
		++i;
	}
	return (0);
}

int		main(void)
{
	t_scene scene;
	t_ray	*ray_list;

	init_scene(&scene);
	ray_list = create_ray_array(ft_translate(0, 0, 2));
	raytracing(ray_list, scene);
	return (0);
}
