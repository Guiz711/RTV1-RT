/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:45:44 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/20 13:51:42 by gmichaud         ###   ########.fr       */
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

static int	pass_spaces(char **data, size_t *line)
{
	int		space_presence;

	space_presence = FALSE;
	while (**data && ft_isspace(**data))
	{
		space_presence = TRUE;
		if (**data == '\n')
			(*line)++;
		(*data)++;
	}
	return (space_presence);
}

static int	verify_header(char **data, size_t *line)
{
	size_t	header_size;
	
	header_size = ft_strlen("RTV1_SCENE:");
	pass_spaces(data, line);
	if (strncmp(*data, "RTV1_SCENE:", header_size))
	{
		error_message("Wrong header, did you mean \"RTV1_SCENE:\"?", *line);
		return (FAILURE);
	}
	*data += header_size;
	return (SUCCESS);
}

static size_t	attribute_len(char *data)
{
	size_t	len;

	len = 0;
	while (!ft_isspace(data[len]) && data[len] != ':' && data[len])
		len++;
	return (len);
}

static int	get_object_type(char **data, t_obj *obj_type, size_t *line, t_parser *parser)
{
	size_t				i;
	size_t				type_len;

	type_len = attribute_len(*data);
	i = 0;
	while (parser->types[i])
	{
		if (type_len == ft_strlen(parser->types[i])
			&& !ft_strncmp(*data, parser->types[i], type_len))
		{
			*obj_type = i + 1;
			*data += ft_strlen(parser->types[i]);
		}
		i++;
	}
	if (*obj_type == NONE)
		return (error_message("Unknown object type.", *line));
	else if (pass_spaces(data, line) && **data == ':')
		return (error_message("Spaces between object type and \':\'", *line));
	else if (**data != ':')
		return (error_message("Missing \':\'.", *line));
	return (SUCCESS);
}

int	parse_sphere(t_scene *scene, char **data, size_t *line, t_props *props)
{
	scene = NULL;
	*data = NULL;
	*line = 0;
	if (!props)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_cam(t_scene *scene, char **data, size_t *line, t_props *props)
{
	scene = NULL;
	*data = NULL;
	*line = 0;
	if (!props)
		return (FAILURE);
	return (SUCCESS);
	/*size_t	prop_len;
	size_t	i;

	while (**data != '}' && **data)
	{
		pass_spaces(data, line);
		prop_len = attribute_len(*data);
		i = 0;
		while (parser->cam_props[i])
		{
			if (prop_len == ft_strlen(parser->cam_props[i])
				&& !ft_strncmp(*data, "origin", prop_len))
			if (init_origin(scene, data, line))
				return (FAILURE);
		}
		else if (prop_len == ft_strlen("orient")
			&& !ft_strncmp(*data, "orient", prop_len))
		{
			if (init_orient(scene, data, line))
				return (FAILURE);
		}
		else
			return (error_message("Unknown object type.", *line));
	}*/
}

static int	parse_object(t_scene *scene, char **data, size_t *line,
	t_parser *parser)
{
	t_obj				obj_type;

	scene = NULL;
	obj_type = NONE;
	pass_spaces(data, line);
	if (get_object_type(data, &obj_type, line, parser))
		return (FAILURE);
	pass_spaces(data, line);
	if (**data != '{')
		return (error_message("Missing \'{\'", *line));
	if (parser->obj_f[obj_type](scene, data, line, parser->props))
		return (FAILURE);
	return (SUCCESS);
}

static int	get_objects(t_scene *scene, char **data, size_t *line)
{
	t_parser	parser;

	if (!init_parser(&parser))
		return (FAILURE);
	pass_spaces(data, line);
	if (**data != '{')
		return (error_message("Missing \'{\'", *line));
	(*data)++;
	/*while(**data)
	{*/
		if (parse_object(scene, data, line, &parser))
			return (FAILURE);
	//}
	return (SUCCESS);
}

static t_err	fill_scene(t_scene *scene, char *file_name)
{
	t_err	err;
	char	*data;
	char	*data_start;
	size_t	line;

	scene = NULL;
	err = NO_ERR;
	data = NULL;
	data_start = NULL;
	line = 1;
	if ((err = read_file(file_name, &data)))
		return (err);
	data_start = data;
	if (verify_header(&data, &line))
		return (ERR_PARSING);
	if (get_objects(scene, &data, &line))
		return (ERR_PARSING);
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
