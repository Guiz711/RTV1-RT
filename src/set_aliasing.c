/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_aliasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:06:23 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 19:45:43 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		multiply_aliasing(t_args *args, double aliasing)
{
	if (aliasing < 2 && aliasing >= 0.5)
	{
		args->env->thread_number = 8;
		aliasing /= 2;
	}
	else if (aliasing >= 2 && aliasing <= 50)
	{
		args->env->thread_number = 1;
		aliasing--;
		if (fmod((args->env->win_width / aliasing), 2) != 0)
		{
			while (fmod((args->env->win_width / aliasing), 2)
					!= 0 && aliasing > 2)
				aliasing--;
		}
	}
	return (aliasing);
}

double		divide_aliasing(t_args *args, double aliasing)
{
	if (aliasing >= 0.25 && aliasing < 1)
	{
		args->env->thread_number = 8;
		aliasing *= 2;
	}
	else if (aliasing >= 1 && aliasing < 50)
	{
		args->env->thread_number = 1;
		aliasing++;
		if (fmod((args->env->win_width / aliasing), 2) != 0)
		{
			while (fmod((args->env->win_width / aliasing), 2) != 0
					&& aliasing < 50)
				aliasing++;
			if (fmod((args->env->win_width / aliasing), 2) != 0)
				aliasing = 50;
		}
	}
	return (aliasing);
}

t_vec3		pix_col_anti(size_t pos, t_vec3 pix_col,
		t_pixel *pix, t_args *args)
{
	t_vec3	pix_tmp;

	pix_tmp = recursive_ray(args, pix[pos].p_ray, 0);
	pix_col.x += pix_tmp.x;
	pix_col.y += pix_tmp.y;
	pix_col.z += pix_tmp.z;
	return (pix_col);
}

size_t		draw_pos_anti(t_args *args, int i, t_pixel *pix, size_t nb_ray)
{
	size_t		j;
	size_t		k;
	size_t		popo;
	t_vec3		pix_col;
	size_t		pos;

	pix_col = (t_vec3){0, 0, 0};
	j = 0;
	popo = 0;
	while (popo++ < nb_ray)
	{
		k = 0;
		pos = ((i % args->env->win_width) * nb_ray) + j +
			(((i / args->env->win_width) * nb_ray) *
			(args->env->win_width * nb_ray));
		while (k++ < nb_ray)
			pix_col = pix_col_anti(k + pos, pix_col, pix, args);
		j += args->env->win_width * nb_ray;
	}
	pix_col.x /= (nb_ray * nb_ray);
	pix_col.y /= (nb_ray * nb_ray);
	pix_col.z /= (nb_ray * nb_ray);
	convert_color(args->env, i, pix_col);
	return (pos);
}
