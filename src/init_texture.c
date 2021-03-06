/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:27:40 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/16 17:28:37 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		load_textures(t_args *args)
{
	int	w;

	w = args->textures.wall.width * (COLOR_DEPTH / 8);
	if (!(args->textures.wall.ptr = mlx_xpm_file_to_image(args->env->init,
			"./textures/brick.xpm", &args->textures.wall.width,
			&args->textures.wall.height)))
		return (0);
	if (!(args->textures.wall.data = mlx_get_data_addr(args->textures.wall.ptr,
			&args->textures.wall.color_depth, &w, &args->textures.wall.endian)))
		return (0);
	w = args->textures.marble.width * (COLOR_DEPTH / 8);
	if (!(args->textures.marble.ptr = mlx_xpm_file_to_image(args->env->init,
			"./textures/floor.xpm", &args->textures.marble.width,
			&args->textures.marble.height)))
		return (0);
	if (!(args->textures.marble.data =
				mlx_get_data_addr(args->textures.marble.ptr,
			&args->textures.marble.color_depth, &w,
			&args->textures.marble.endian)))
		return (0);
	return (1);
}

int		init_textures(t_args *args)
{
	args->textures.wall.color_depth = 64;
	args->textures.wall.width = 1024;
	args->textures.wall.height = 1024;
	args->textures.wall.endian = 0;
	args->textures.wall.ptr = NULL;
	args->textures.wall.data = NULL;
	args->textures.marble.color_depth = 64;
	args->textures.marble.width = 1024;
	args->textures.marble.height = 1024;
	args->textures.marble.endian = 0;
	args->textures.marble.ptr = NULL;
	args->textures.marble.data = NULL;
	if (!load_textures(args))
		return (0);
	return (1);
}

void	add_texture(t_scene *scene)
{
	t_obj_lst		*tmp;
	unsigned int	id;

	tmp = scene->objs;
	id = 0;
	while (tmp)
	{
		tmp->material.bump_text = NO_BUMP;
		tmp->material.bump_angle = -60;
		tmp->material.bump_scale = 0.25;
		tmp->material.absorb = init_vec3(0, 0, 0);
		tmp = tmp->next;
	}
}
