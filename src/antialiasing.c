/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 07:59:35 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/28 04:04:21 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
int		val(t_env *env)
{
	static size_t p = 0;
	static int  x = 0;

	if  ((p * 100)/ (WIN_WIDTH * WIN_HEIGHT) >= 1)
	{
		mlx_put_image_to_window(env->init, env->win, env->loadbar->ptr, x, 650);
		x += WIN_WIDTH / 100;
		p = 0;
	}
	

	return (++p);
}



int		set_aliasing(int keycode, t_args *args)
{
	double	aliasing;

	aliasing = args->env->aliasing;
	if (keycode == KEY_MULTIPLY)
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
				while (fmod((args->env->win_width / aliasing), 2) != 0 && aliasing > 2)
					aliasing--;
			}
		}
	}
	else if (keycode == KEY_DIVIDE)
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
				while (fmod((args->env->win_width / aliasing), 2) != 0 && aliasing < 50)
					aliasing++;
				if (fmod((args->env->win_width / aliasing), 2) != 0)
					aliasing = 50;
			}
		}
	}
	if (args->env->aliasing == aliasing)
		return (0);
	args->env->aliasing = aliasing;
	return (1);
}

void	antiAliasing(t_args *args, t_pixel *pix, size_t i, size_t end)
{
	t_vec3		pix_col;
	t_vec3		pix_tmp;
	size_t		nb_ray;
	size_t		j;
	size_t		k;
	size_t		pos;
	size_t		popo;

	nb_ray = 1 / args->env->aliasing;
	while (i < end)
	{
		j = 0;
		popo = 0;
		pix_col = (t_vec3){0, 0, 0};
		while (popo++ < nb_ray)
		{
			k = 0;
			pos = ((i % args->env->win_width) * nb_ray) + j + (((i / args->env->win_width) * nb_ray) *  (args->env->win_width * nb_ray));
			while (k++ < nb_ray)
			{
				pix_tmp = recursive_ray(args, pix[pos + k].p_ray, 0, pos + k),
						pix_col.x += pix_tmp.x;
				pix_col.y += pix_tmp.y;
				pix_col.z += pix_tmp.z;
			}
			j += args->env->win_width * nb_ray;
		}
		pix_col.x /= (nb_ray * nb_ray);
		pix_col.y /= (nb_ray * nb_ray);
		pix_col.z /= (nb_ray * nb_ray);
		//val(args->env);
		convert_color(args->env, i, pix_col);
		++i;
	}
	return;
}

void	Aliasing(t_args *args, t_pixel *pix, size_t i, size_t end)
{
	t_vec3		pix_col;
	int			pos;
	size_t		pr_pos;
	size_t		nb_pix;
	size_t		h;
	size_t		w;
	size_t		compteur;

	compteur = 0;
	nb_pix = args->env->aliasing;
	pos = (i / (nb_pix * nb_pix)) - 1;
	while (i < end)
	{
		h = 0;
		if (pos < (int)((((WIN_HEIGHT / nb_pix) * (WIN_WIDTH / nb_pix)) / args->env->thread_number) * (end / ((WIN_HEIGHT *  WIN_WIDTH) / args->env->thread_number ))))
			++pos;
		pix_col = recursive_ray(args, pix[pos].p_ray, 0, pos);
		while (h < nb_pix)
		{
			w = 0;
			pr_pos = i + (h * (args->env->win_width));
			while (w < nb_pix)
			{
				//val(args->env);
				convert_color(args->env, pr_pos + w, pix_col);
				w++;
			}
			h++;
		}
		i += nb_pix;
		compteur++;
		if (compteur == (args->env->win_width / nb_pix))
		{
			i += args->env->win_width * (nb_pix - 1);
			compteur = 0;
		} 
	}


}
