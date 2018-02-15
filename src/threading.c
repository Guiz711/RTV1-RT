/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:45:40 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/15 20:35:34 by gmichaud         ###   ########.fr       */
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

int		double_not_null(double d)
{
	if (d > 1e-6 || d < -1e-6)
		return TRUE;
	return FALSE;
}

t_ray	refracted_ray(t_vec4 ray_dir, t_inter *inter)
{
	t_ray	refr;
	double	r_ratio;
	double	c1;
	double	c2;

	c1 = dot_vec4(inter->normal, ray_dir);
	if (c1 < 0)
	{
		r_ratio = 1 / inter->obj->material.refract;
		c2 = sqrt(1 - SQUARE(r_ratio) * (1 - SQUARE(-c1)));
		refr.dir = add_vec4(dmult_vec4(ray_dir, r_ratio),
			dmult_vec4(inter->normal, (r_ratio * -c1) - c2));
		refr.orig = add_vec4(inter->p, dmult_vec4(inter->normal, -0.0000007));
	}
	else
	{
		r_ratio = inter->obj->material.refract;
		c2 = sqrt(1 - SQUARE(r_ratio) * (1 - SQUARE(c1)));
		refr.dir = add_vec4(dmult_vec4(ray_dir, r_ratio),
			dmult_vec4(rev_vec4(inter->normal), (r_ratio * c1) - c2));
		refr.orig = add_vec4(inter->p, dmult_vec4(inter->normal, 0.0000007));
	}
	refr.range = 1e6;
	return (refr);
}

void	invert(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}

double	fresnel_calc(t_vec4 normal, t_vec4 ray_dir, double n1, double n2)
{
	double	refl;
	double	ndotr;
	double	r0;
	double	ratio;
	double 	sinx;

	ndotr = dot_vec4(normal, ray_dir);
	if (ndotr < 0)
		invert(&n1, &n2);
	ndotr = dot_vec4(normal, ray_dir);
	r0 = SQUARE((n1 - n2) / (n1 + n2));
	if (n2 > n1)
	{
		ratio = n2 / n1;
		sinx = SQUARE(ratio) * (1 - SQUARE(ndotr));
		if (sinx > 1)
			return (1);
		ndotr = -sqrt(1 - sinx);
	}
	refl = r0 + (1 - r0) * pow((1 + ndotr), 5);
	return (refl);
}

t_vec3	recursive_ray(t_args *args, t_ray ray, int depth, size_t i)
{
	t_ray	reflect;
	t_ray	refract;
	t_inter	inter;
	t_color	color_comp;
	t_vec3	prim_color;
	t_vec3	refl_color;
	t_vec3	refr_color;
	double	refl_ratio;
	double	diff_ratio;
	
	if (depth > REFLEXION_DEPTH)
		return (init_vec3(0, 0, 0));
	color_comp.amb_ratio = init_vec3(0, 0, 0);
	color_comp.diff_ratio = init_vec3(0, 0, 0);
	color_comp.spec_ratio = init_vec3(0, 0, 0);
	prim_color = init_vec3(0, 0, 0);
	refl_color = init_vec3(0, 0, 0);
	refr_color = init_vec3(0, 0, 0);
	inter = trace_ray(ray, args->scene->objs, args->obj_fct, 0);
	if (inter.obj)
	{
		// if (i == 455731)
			// printf("inter_obj: %d\n", inter.obj->id_obj);
		inter.normal = args->norm_fct[inter.obj->content_type](&ray, &inter);
		args->rdr_fct[args->scene->render_mode](args, &ray, &inter, &color_comp);
		prim_color = add_vec3(color_comp.spec_ratio,
			dmult_vec3(add_vec3(color_comp.diff_ratio, color_comp.amb_ratio), inter.obj->material.reflect.x));
		// prim_color = add_vec3(color_comp.spec_ratio,
			// add_vec3(color_comp.diff_ratio, color_comp.amb_ratio));
		refl_ratio = fresnel_calc(inter.normal, ray.dir, 1, inter.obj->material.refract);
		refl_ratio = inter.obj->material.reflect.y + (1.0 - inter.obj->material.reflect.y) * refl_ratio;
		// refl_ratio = inter.obj->material.reflect.y * refl_ratio;
		if (inter.obj->material.reflect.y != 0)
		{
			reflect = reflected_ray(ray.dir, &inter);
			refl_color = recursive_ray(args, reflect, depth + 1, i);
			refl_color = dmult_vec3(refl_color, refl_ratio);
		}
		if (double_not_null(1 - inter.obj->material.reflect.x))
		{
			refract = refracted_ray(ray.dir, &inter);
			refr_color = recursive_ray(args, refract, depth + 1, i);
			//refr_color = mult_vec3(refr_color, inter.obj->material.diff);
		}
		diff_ratio = 1 - refl_ratio;
		refr_color = dmult_vec3(refr_color, diff_ratio * (1 - inter.obj->material.reflect.x));
		// refr_color = dmult_vec3(refr_color, diff_ratio);
	}
	return (add_vec3(prim_color, add_vec3(refr_color, refl_color)));
}

static void	*trace_rays_threads(void *vt_args)
{
	t_args		*args;
	size_t		i;
	t_pixel		*pix;
	t_vec3		pix_col;

	args = ((t_thread*)vt_args)->args;
	pix = args->pix_buf;
	i = ((t_thread*)vt_args)->start;
	while (i < ((t_thread*)vt_args)->end)
	{
		pix_col = recursive_ray(args, pix[i].p_ray, 0, i);
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
