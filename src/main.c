/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:44:07 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/01 13:31:43 by gmichaud         ###   ########.fr       */
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

int		check_intersection(t_vec4 dir, t_vec4 orig, t_vec4 ctr, double radius)
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
		return (0);
	else if (disc == 0)
		return (1);
	return (2);
}

int		check_intersections(t_ray ray, t_scene scn)
{
	t_sphere	*sph;
	int			inter;

	while (scn.items)
	{
		sph = (t_sphere*)scn.items->content;
		inter = check_intersection(ray.dir, ray.orig, sph->center, sph->radius);
		if (inter)
			
		scn.items = scn.items->next;
	}
}

int		main(void)
{
	t_scene scene;
	t_ray	*ray_list;

	init_scene(&scene);
	ray_list = create_ray_array(ft_translate(0, 0, 2));
	check_intersections(ray_list, scene);
	printf("%f", ((t_sphere*)scene.items->content)->radius);
	return (0);
}
