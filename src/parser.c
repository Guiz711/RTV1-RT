/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:45:44 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/27 18:17:08 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_error	verify_extension(char *file_name)
{
	size_t	extension_size;
	size_t	len;

	extension_size = ft_strlen(EXTENSION_NAME);
	len = ft_strlen(file_name);
	if (len < extension_size + 1)
		return (FAILURE);
	if (ft_strcmp(file_name + len - extension_size, EXTENSION_NAME))
		return (FAILURE);
	return (SUCCESS);
}

static void	init_scene(t_scene *scene)
{
	scene->items = NULL;
	scene->cam.orig.x = 0;
	scene->cam.orig.y = 0;
	scene->cam.orig.z = 0;
	scene->cam.orig.w = 1;
	scene->cam.orient = 0;
}

static t_error	fill_scene(t_scene *scene, char *file_name)
{
	int		error;
	char	*data;
	char	*data_start;

	error = 0;
	data = NULL;
	data_start = NULL;
	if ((error = read_file(file_name, data)))
		return (error);
	data_start = data;
	if (verify_header(data))
		return (ERR_FILE_HEADER);
	if (get_objects(data))
		return (ERR_PARSING);
}

t_scene		*parse_scene_file(char *file_name, int *err)
{
	t_scene	*scene;

	if (verify_extension(file_name))
		return (NULL);
	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
	{
		
		return (error_malloc(NULL));
	}
	init_scene(scene);
	if ((error = fill_scene(scene, file_name)))
		return (NULL);
	return (scene);
}
