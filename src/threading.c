/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:45:40 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/26 11:00:00 by gmichaud         ###   ########.fr       */
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

static void	*trace_rays_threads(void *vt_args)
{
	t_args		*args;
	size_t		i;
	t_pixel		*pix;
	t_vec3		pix_col;
	int			y;

	y = -1;
	args = ((t_thread*)vt_args)->args;
	pix = args->pix_buf;
	i = ((t_thread*)vt_args)->start;
	while (i < ((t_thread*)vt_args)->end)
	{
		if ((unsigned int)y == args->env->aliasing || y == -1)
		{
			pix_col = recursive_ray(args, pix[i].p_ray, 0, i);
			y = -1;
		}
		convert_color(args->env, i, pix_col);
		++i;
		++y;
	}
	return (NULL);
}

int		manage_threads(t_args *args)
{
	pthread_t	t[THREADS_NUMBER];
	t_thread	thread[THREADS_NUMBER];
	int			i;

	i = 0;
	if (args->env->moving == 1)
		check_hook(args);
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
	init_hook(args->env);
	return (SUCCESS);
}
