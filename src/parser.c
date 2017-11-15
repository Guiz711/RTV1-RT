/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:45:44 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/15 11:56:09 by gmichaud         ###   ########.fr       */
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
	size_t	header_size;
	
	header_size = ft_strlen("RTV1_SCENE:");
	while (**data && ft_isspace(**data))
		(*data)++;
	if (strncmp(*data, "RTV1_SCENE:", header_size))
		return (FAILURE);
	*data += header_size;
	return (SUCCESS);
}

/*static size_t	len_without_spaces(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (!ft_isspace(*str))
			len++;
		str++;
	}
	return (len);
}

static char		*strcat_without_spaces(char *dest, const char *src)
{
	char	*dest_begin;

	dest_begin = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		if (!ft_isspace(*src))
			*dest++ = *src;
		src++;
	}
	return (dest_begin);
}*/

static t_err	file_len(char *file_name, size_t *file_size)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (ERR_OPEN);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		*file_size += ft_strlen(buffer);
	}
	if (ret == -1)
		return (ERR_READ);
	if (*file_size == 0)
		return (ERR_FILE_EMPTY);
	close(fd);
	return (NO_ERR);
}

static t_err	get_data(char *file_name, char **data)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (ERR_OPEN);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		ft_strcat(*data, buffer);
	}
	if (ret == -1)
		return (ERR_READ);
	close(fd);
	return (NO_ERR);
}

static t_err	read_file(char *file_name, char **data)
{
	t_err	err;
	size_t	file_size;

	err = NO_ERR;
	file_size = 0;
	if ((err = file_len(file_name, &file_size)))
		return (err);
	if (!(*data = ft_strnew(sizeof(**data) * file_size)))
		return (ERR_MALLOC);
	if ((err = get_data(file_name, data)))
		return (err);
	return (NO_ERR);
}

static t_err	fill_scene(t_scene *scene, char *file_name)
{
	t_err	err;
	char	*data;
	char	*data_start;

	err = NO_ERR;
	data = NULL;
	scene = NULL;
	data_start = NULL;
	if ((err = read_file(file_name, &data)))
		return (err);
	data_start = data;
	if (verify_header(&data))
		return (ERR_FILE_HEADER);
	/*if (get_objects(&data))
		return (error(ERR_PARSING));*/
	return (NO_ERR);
}

t_err			parse_scene_file(t_scene *scene, char *file_name)
{
	t_err	err;

	err = NO_ERR;
	if (verify_extension(file_name))
		return (ERR_FILE_EXTENSION);
	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		return (ERR_MALLOC);
	init_scene(scene);
	if ((err = fill_scene(scene, file_name)))
		return (err);
	return (NO_ERR);
}
