/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:45:40 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/09 13:55:42 by gmichaud         ###   ########.fr       */
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

t_ray	reflected_ray(t_ray *ray, t_inter *inter, t_vec4 normal)
{
	t_vec4 dir;
	double ndotr;
	t_ray refl;

	dir = normalize_vec4(rev_vec4(sub_vec4(inter->p, ray->dir)));
	ndotr = 2 * dot_vec4(normal, dir);
	refl.dir = normalize_vec4(sub_vec4(dmult_vec4(normal, ndotr), dir));
	refl.orig = add_vec4(inter->p, dmult_vec4(normal, 0.0000007));
	refl.range = 1e6;
	return (refl);
}

void	recursive_ray(t_args *args, t_pixel *pix, t_ray ray, size_t pos, int depth)
{
	//t_ray	reflected;
	
	if (depth > REFLEXION_DEPTH)
		return ;
	pix->inter = trace_ray(ray, args->scene->objs, args->obj_fct, 0);
	if (pix->inter.obj)
	{
		pix->normal = args->norm_fct[pix->inter.obj->content_type](pix);
		args->rdr_fct[args->scene->render_mode](args, pix, pos);
		pix->p_ray = reflected_ray(&ray, &pix->inter, pix->normal);
		recursive_ray(args, pix, pix->p_ray, pos, depth + 1);
	}
}

static void	*trace_rays_threads(void *vt_args)
{
	t_args		*args;
	size_t		i;
	t_pixel		*pix;

	args = ((t_thread*)vt_args)->args;
	pix = args->pix_buf;
	i = ((t_thread*)vt_args)->start;
	while (i < ((t_thread*)vt_args)->end)
	{
		recursive_ray(args, &pix[i], pix[i].p_ray, i, 0);
		// pix[i].inter = trace_ray(pix[i].p_ray, args->scene->objs,
		// 	args->obj_fct, 0);
		// if (pix[i].inter.obj)
		// {
		// 	pix[i].normal =
		// 		args->norm_fct[pix[i].inter.obj->content_type](&pix[i]);
		// }
		// args->rdr_fct[args->scene->render_mode](args, &pix[i], i);
		process_color(args->env, &pix[i], i);
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
