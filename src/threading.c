/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:45:40 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/15 04:15:18 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <limits.h>

void	init(t_thread *t, t_args *args)
{
	size_t	len;
	size_t	i;

	len = args->env->win_height * args->env->win_width;
	i = 0;
	while (i < THREADS_NUMBER)
	{
		t[i].args = args;
		t[i].start = (i == 0) ? 0 : len / THREADS_NUMBER * i;
		t[i].end = (i == THREADS_NUMBER - 1) ? len
			: len / THREADS_NUMBER * (i + 1);
		i++;
	}
}

t_ray	reflected_ray(t_vec4 ray_dir, t_inter *inter)
{
	double	ndotr;
	t_ray	refl;

	ndotr = dot_vec4(inter->normal, ray_dir);
	refl.dir = normalize_vec4(add_vec4(ray_dir,
		dmult_vec4(inter->normal, -2 * ndotr)));
	refl.orig = add_vec4(inter->p, dmult_vec4(inter->normal, 0.0000007));
	refl.range = 1e6;
	return (refl);
}

t_vec3	recursive_ray(t_args *args, t_ray ray, int depth, size_t i)
{
	t_ray	refl;
	t_inter	inter;
	t_color	color_comp;
	t_vec3	prim_color;
	t_vec3	refl_color;
	
	if (depth > REFLEXION_DEPTH)
		return (init_vec3(0, 0, 0));
	color_comp.amb_ratio = init_vec3(0, 0, 0);
	color_comp.diff_ratio = init_vec3(0, 0, 0);
	color_comp.spec_ratio = init_vec3(0, 0, 0);
	prim_color = init_vec3(0, 0, 0);
	refl_color = init_vec3(0, 0, 0);
	inter = trace_ray(ray, args->scene->objs, args->obj_fct, 0);
	if (inter.obj)
	{
		inter.normal = args->norm_fct[inter.obj->content_type](&ray, &inter);
		args->rdr_fct[args->scene->render_mode](args, &ray, &inter, &color_comp);
		prim_color = add_vec3(color_comp.amb_ratio,
			add_vec3(color_comp.diff_ratio, color_comp.spec_ratio));
		refl = reflected_ray(ray.dir, &inter);
		refl_color = recursive_ray(args, refl, depth + 1, i);
		refl_color = mult_vec3(refl_color, inter.obj->material.refl);
	}
	return (add_vec3(prim_color, refl_color));
}

static void	*trace_rays_threads(void *vt_args)
{
	t_args		*args;
	size_t		i;
	t_pixel		*pix;
	t_vec3		pix_col;
	int			y;

	y = 4;
	args = ((t_thread*)vt_args)->args;
	pix = args->pix_buf;
	i = ((t_thread*)vt_args)->start;
	while (i < ((t_thread*)vt_args)->end)
	{
		if (y == 36)
		{
			pix_col = recursive_ray(args, pix[i].p_ray, 0, i);
			y = 0;
		}
		y++;
		convert_color(args->env, i, pix_col);
		++i;
	}
	return (NULL);
}

int		manage_threads(t_args *args)
{
	pthread_t	t[THREADS_NUMBER];
	t_thread	thread[THREADS_NUMBER];
	int			i;

	i = 0;
	init(&thread[0], args);
	while (i < THREADS_NUMBER)
	{
		if (pthread_create(&t[i], NULL, &trace_rays_threads, &thread[i]))
		{
			while (i--)
				pthread_cancel(t[i]);
			return (FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < THREADS_NUMBER)
	{
		if (pthread_join(t[i], NULL))
			return (FAILURE);
		i++;
	}
	mlx_put_image_to_window(args->env->init, args->env->win, args->env->img->ptr, 0, 0);
	return (SUCCESS);
}
