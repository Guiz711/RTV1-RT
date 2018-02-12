/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:45:40 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/12 12:40:39 by gmichaud         ###   ########.fr       */
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

void	reflected_ray(t_ray *ray, t_inter *inter, t_vec4 normal)
{
	// t_vec4 dir;
	double ndotr;

	//dir = normalize_vec4(rev_vec4(sub_vec4(inter->p, ray->dir)));
	ndotr = dot_vec4(normal, ray->dir);
	ray->dir = normalize_vec4(add_vec4(ray->dir, dmult_vec4(normal, -2 * ndotr)));
	//printf("%f, %f, %f, %f\n", refl.dir.x, refl.dir.y, refl.dir.z, refl.dir.w);
	ray->orig = add_vec4(inter->p, dmult_vec4(normal, 0.0000007));
}

t_vec3	recursive_ray(t_args *args, t_pixel *pix, int depth, size_t i)
{
	t_vec3	prim_color;
	t_vec3	refl_color;
	// t_ray	refl;
	
	if (depth > REFLEXION_DEPTH)
		return (init_vec3(0, 0, 0));
	prim_color = init_vec3(0, 0, 0);
	refl_color = init_vec3(0, 0, 0);
	pix->inter = trace_ray(pix->p_ray, args->scene->objs, args->obj_fct, 0);
	if (pix->inter.obj)
	{
		if (i == 552428)
			printf("%f\n", ((t_sphere*)pix->inter.obj->content)->center.x);
		pix->inter.normal = args->norm_fct[pix->inter.obj->content_type](pix);
		args->rdr_fct[args->scene->render_mode](args, pix);
		prim_color = add_vec3(pix->amb_ratio, add_vec3(pix->diff_ratio, pix->spec_ratio));
		pix->amb_ratio = init_vec3(0, 0, 0);
		pix->diff_ratio = init_vec3(0, 0, 0);
		pix->spec_ratio = init_vec3(0, 0, 0);
		//refl = reflected_ray(&ray, &pix->inter, pix->inter.normal);
		reflected_ray(&pix->p_ray, &pix->inter, pix->inter.normal);
		// if (i == 552428)
			// printf("reflected : %f, %f, %f\n", refl.dir.x, refl.dir.y, refl.dir.z);
		refl_color = recursive_ray(args, pix, depth + 1, i);
	}
	if (i == 552428)
		printf("%f, %f, %f\n", refl_color.x, refl_color.y, refl_color.z);
	return (add_vec3(prim_color, dmult_vec3(refl_color, 0.8)));
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
		pix_col = recursive_ray(args, &pix[i], 0, i);
		// pix[i].inter = trace_ray(pix[i].p_ray, args->scene->objs,
		// 	args->obj_fct, 0);
		// if (pix[i].inter.obj)
		// {
		// 	pix[i].normal =
		// 		args->norm_fct[pix[i].inter.obj->content_type](&pix[i]);
		// }
		// args->rdr_fct[args->scene->render_mode](args, &pix[i], i);
		process_color(args->env, &pix[i], i, pix_col);
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
	return (SUCCESS);
}
