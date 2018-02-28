/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 01:27:29 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/28 00:26:02 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		init_loadingscreen(t_env *env)
{
	t_img	*img;
	t_img	*load;

	if (!(load = (t_img*)malloc(sizeof(t_img))))
		return (FAILURE);
	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (FAILURE);
	img->ptr = mlx_xpm_file_to_image(env->init, "./pics/loadingscreen.xpm", &img->width,
			&img->height);
	load->ptr = mlx_xpm_file_to_image(env->init, "./pics/loadbar.xpm",
		&load->width, &load->height);
	env->lodscreen = img;
	env->loadbar = load;
	mlx_put_image_to_window(env->init, env->win, env->lodscreen->ptr, 0, 0);
	return (SUCCESS);
}
