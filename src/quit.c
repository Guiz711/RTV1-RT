/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:45:42 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 14:51:16 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		free_obj_lst(t_obj_lst **obj_lst)
{
	t_obj_lst	*tmp;

	if (obj_lst)
	{
		tmp = (*obj_lst)->next;
		while (tmp)
		{
			free((*obj_lst)->content);
			free(*obj_lst);
			*obj_lst = tmp;
			tmp = tmp->next;
		}
		*obj_lst = NULL;
		free(tmp);
	}
}

static void		free_light(void *content, size_t content_size)
{
	if (content_size)
		free((t_light*)content);
}

int				quit(t_args *args)
{
	if (!args)
		exit(EXIT_SUCCESS);
	if (args->env->lodscreen)
		mlx_destroy_image(args->env->init, args->env->lodscreen->ptr);
	if (args->textures.marble.ptr)
		mlx_destroy_image(args->env->init, args->textures.marble.ptr);
	if (args->textures.wall.ptr)
		mlx_destroy_image(args->env->init, args->textures.wall.ptr);
	if (args->env->img)
		mlx_destroy_image(args->env->init, args->env->img->ptr);
	if (args->scene->objs)
		free_obj_lst(&args->scene->objs);
	if (args->scene->light)
		ft_lstdel(&args->scene->light, &free_light);
	if (args->pix_buf)
		free(args->pix_buf);
	if (args->env->win)
		mlx_destroy_window(args->env->init, args->env->win);
	if (args->env->init)
		free(args->env->init);
	exit(EXIT_SUCCESS);
}
