/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 09:47:55 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/20 01:17:18 by jgourdin         ###   ########.fr       */
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
	// if (args->env->init)
	// 	free(args->env->init);
	exit(EXIT_SUCCESS);
}

int			redraw(t_args *args)
{

	if (args->scene->objs)
		free_obj_lst(&args->scene->objs);
	if (args->scene->light)
		ft_lstdel(&args->scene->light, &free_light);
	args->scene->objs = NULL;
	args->scene->light = NULL;
	if(!xml_parse(args->scene->path, args->scene))
		exit(-1);
	free(args->pix_buf);
	args->pix_buf = init_pix_buffer(args->env, get_camera_to_world(&args->scene->cam));
	manage_threads(args);
	return (1);
}

