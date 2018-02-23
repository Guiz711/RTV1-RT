/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 07:59:35 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/23 09:38:34 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		set_aliasing(int keycode, t_args *args)
{
	double	aliasing;
	int		popo;

	aliasing = args->env->aliasing;
	popo = aliasing - 1;
	if (keycode == KEY_MULTIPLY)
	{
		if (aliasing <= 2 && aliasing >= 0.5)
			aliasing /= 2;
		else if (aliasing <= 50 && aliasing >= 0.25)
		{
			while ((int)(args->env->win_width / aliasing) % 2 != 0)
				aliasing--;
			if ((int)(args->env->win_width / aliasing) % 2 != 0)
				aliasing = args->env->aliasing;
		}
	}
	else if (keycode == KEY_DIVIDE)
	{
		if (aliasing >= 0.25 && aliasing <= 1)
		{
			aliasing *= 2;
		}
		else if (aliasing >= 2 && aliasing <= 50)
		{
			while ((int)(args->env->win_width / aliasing) % 2 != 0)
				aliasing++;
			if ((int)(args->env->win_width / aliasing) % 2 != 0)
				aliasing = args->env->aliasing;
		}
	}
	printf("%f\n", aliasing);
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

	pos = -1;
	compteur = 0;
	nb_pix = args->env->aliasing;
	while (i < end)
	{
		h = 0;
		++pos;
		pix_col = recursive_ray(args, pix[pos].p_ray, 0, pos);
		while (h < nb_pix)
		{
			w = 0;
			pr_pos = i + (h * (args->env->win_width));
			while (w < nb_pix)
			{
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
		printf("pos = %d, %d %d\n", pos, args->env->win_width, (int)(i % ((args->env->win_width / 2) - 1)));
	}
}
