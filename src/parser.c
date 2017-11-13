/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:45:44 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/13 12:58:24 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	verify_extension(char *file_name)
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

static int	verify_header(char **data)
{
	if (strncmp(*data, "RTV1_SCENE:", sizeof(**data) * 11))
		return (FAILURE);
	return (SUCCESS);
}

static int	file_len(char *file_name, size_t *file_size, t_error *err)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return(error(ERR_OPEN, err));
	while (ret = read(fd, buffer, BUFF_SIZE)
	{
		buffer[ret] = '\0';
		file_size += ft_strlen(buffer);
	}
	if (ret == -1)
		return(error(ERR_READ, err));
	close(fd);
	return (SUCCESS);
}

static int	read_file(char *file_name, char *data, t_error *err)
{
	size_t	file_size;

	file_size = 0;
	if (file_len(file_name, &file_size, err))
		return (FAILURE);
	return (SUCCESS);
}

static int	fill_scene(t_scene *scene, char *file_name, t_error *err)
{
	char	*data;
	char	*data_start;

	data = NULL;
	data_start = NULL;
	if (read_file(file_name, data, err))
		return (FAILURE);
	/*data_start = data;
	if (verify_header(&data))
		return (error(ERR_FILE_HEADER));
	if (get_objects(&data))
		return (error(ERR_PARSING));*/
	return (SUCCESS);
}

int			parse_scene_file(t_scene *scene, char *file_name, t_error *err)
{
	if (verify_extension(file_name))
		return (error(ERR_FILE_EXTENSION, err));
	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		return (error(ERR_MALLOC, err));
	init_scene(scene);
	if (fill_scene(scene, file_name, err))
		return (FAILURE);
	return (SUCCESS);
}
