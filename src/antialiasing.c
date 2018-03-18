/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 07:59:35 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 19:43:18 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		set_aliasing(int keycode, t_args *args)
{
	double	aliasing;

	aliasing = args->env->aliasing;
	if (keycode == KEY_MULTIPLY)
		aliasing = multiply_aliasing(args, aliasing);
	else if (keycode == KEY_DIVIDE)
		aliasing = divide_aliasing(args, aliasing);
	if (args->env->aliasing == aliasing)
		return (0);
	args->env->aliasing = aliasing;
	return (1);
}

void	antialiasing(t_args *args, t_pixel *pix, size_t i, size_t end)
{
	t_vec3		pix_col;
	size_t		nb_ray;
	size_t		pos;

	nb_ray = 1 / args->env->aliasing;
	while (i < end)
	{
		pix_col = (t_vec3){0, 0, 0};
		pos = draw_pos_anti(args, i, pix, nb_ray);
		++i;
	}
}

void	aliasing(t_args *args, t_pixel *pix, size_t i, size_t end)
{
	t_vec3		pix_col;
	int			pos;
	size_t		nb_pix;
	size_t		compteur;

	compteur = 0;
	nb_pix = args->env->aliasing;
	pos = (i / (nb_pix * nb_pix)) - 1;
	while (i < end)
	{
		if (pos < (int)((((WIN_HEIGHT / nb_pix) * (WIN_WIDTH / nb_pix)) /
				args->env->thread_number) * (end / ((WIN_HEIGHT * WIN_WIDTH)
					/ args->env->thread_number))))
			++pos;
		pix_col = recursive_ray(args, pix[pos].p_ray, 0);
		draw_pos_alia(args, pix_col, nb_pix, i);
		i += nb_pix;
		compteur++;
		if (compteur == (args->env->win_width / nb_pix))
		{
			i += args->env->win_width * (nb_pix - 1);
			compteur = 0;
		}
	}
}
