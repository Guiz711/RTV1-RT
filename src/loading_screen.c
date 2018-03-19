/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 01:27:29 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 14:24:24 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		init_loadingscreen(t_env *env)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (FAILURE);
	img->ptr = mlx_xpm_file_to_image(env->init,
			"./pics/loadingscreen.xpm", &img->width, &img->height);
	env->lodscreen = img;
	mlx_put_image_to_window(env->init, env->win, env->lodscreen->ptr, 0, 0);
	return (SUCCESS);
}
