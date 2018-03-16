/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_aliasing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 11:54:32 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/16 12:01:29 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		draw_pos_alia(t_args *args, t_vec3 pix_col, size_t nb_pix, size_t i)
{
	size_t		w;
	size_t		pr_pos;
	size_t		h;

	h = 0;
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
}
