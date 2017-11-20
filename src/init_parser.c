/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:13:39 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/20 13:54:09 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	fill_types_table(char **types)
{
	if (!(types[0] = ft_strdup("camera")))
		return (FAILURE);
	if (!(types[1] = ft_strdup("sphere")))
		return (FAILURE);
	if (!(types[2] = ft_strdup("cylinder")))
		return (FAILURE);
	if (!(types[3] = ft_strdup("cone")))
		return (FAILURE);
	if (!(types[4] = ft_strdup("plan")))
		return (FAILURE);
	types[5] = NULL;
	return (SUCCESS);
}

static int	fill_cam_table(char **cam_props)
{
	if (!(cam_props[0] = ft_strdup("origin")))
		return (FAILURE);
	if (!(cam_props[1] = ft_strdup("orient")))
		return (FAILURE);
	cam_props[2] = NULL;
	return (SUCCESS);
}

static int	fill_sph_table(char **sph_props)
{
	if (!(sph_props[0] = ft_strdup("origin")))
		return (FAILURE);
	if (!(sph_props[1] = ft_strdup("radius")))
		return (FAILURE);
	if (!(sph_props[2] = ft_strdup("color")))
		return (FAILURE);
	sph_props[3] = NULL;
	return (SUCCESS);
}

int			init_props(t_props *props)
{
	if (!(props->cam = (char**)ft_memalloc(sizeof(char*) * 3)))
		return (FAILURE);
	if (!fill_cam_table(props->cam))
		return (FAILURE);
	if (!(props->sph = (char**)ft_memalloc(sizeof(char*) * 4)))
		return (FAILURE);
	if (!fill_sph_table(props->sph))
		return (FAILURE);
	return (SUCCESS);
}

int			init_parser(t_parser *parser)
{
	if (!(parser->types = (char**)ft_memalloc(sizeof(char*) * 6)))
		return (FAILURE);
	if (!fill_types_table(parser->types))
		return (FAILURE);
	if (!(parser->obj_f = (t_fctn*)ft_memalloc(sizeof(t_fctn) * 3)))
		return (FAILURE);
	parser->obj_f[0] = &parse_cam;
	parser->obj_f[1] = &parse_sphere;
	if (!(parser->props = (t_props*)ft_memalloc(sizeof(t_props))))
		return (FAILURE);
	if (init_props(parser->props))
		return (FAILURE);
	return (SUCCESS);
}
