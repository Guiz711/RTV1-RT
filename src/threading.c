/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:21:06 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 16:22:39 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <limits.h>

t_vec3		ft_average(t_vec3 c1, t_vec3 c2)
{
	t_vec3	final;

	final.x = (c1.x + c2.x) / 2;
	final.y = (c1.y + c2.y) / 2;
	final.z = (c1.z + c2.z) / 2;
	return (final);
}

int			display_image(t_args *args)
{
	filter_selector(args);
	mlx_put_image_to_window(args->env->init, args->env->win,
		args->env->img->ptr, 0, 0);
	init_hook(args->env);
	return (SUCCESS);
}

void		init(t_thread *t, t_args *args)
{
	size_t	len;
	size_t	i;

	len = args->env->win_height * args->env->win_width;
	i = 0;
	while ((int)i < args->env->thread_number)
	{
		t[i].args = args;
		t[i].start = (i == 0) ? 0 : len / args->env->thread_number * i;
		t[i].end = ((int)i == args->env->thread_number - 1) ? len
			: len / args->env->thread_number * (i + 1);
		i++;
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
	if (args->env->aliasing <= 1)
		antialiasing(args, pix, i, ((t_thread*)vt_args)->end);
	else
		aliasing(args, pix, i, ((t_thread*)vt_args)->end);
	return (NULL);
}

int			manage_threads(t_args *args)
{
	pthread_t	t[args->env->thread_number];
	t_thread	thread[args->env->thread_number];
	int			i;

	i = 0;
	if (args->env->moving == 1)
		check_hook(args);
	init(&thread[0], args);
	while (i < args->env->thread_number)
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
	while (i < args->env->thread_number)
	{
		if (pthread_join(t[i++], NULL))
			return (FAILURE);
	}
	return (display_image(args));
}
