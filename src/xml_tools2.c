/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:12:03 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 15:46:04 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

void				shd_scene(int *shd_arr, char *string)
{
	char			**db;
	int				i;
	int				p;

	i = -1;
	p = -1;
	db = ft_strsplit(string, '|');
	while (db[++i])
	{
		if (ft_strcmp(db[i], "LAMBERT") == 0)
			p = LAMBERT;
		else if (ft_strcmp(db[i], "PHONG") == 0)
			p = PHONG;
		else
			p = -1;
		if (p != -1)
			shd_arr[p] = 1;
	}
	i = -1;
	while (db[++i])
		ft_strdel(&db[i]);
	free(db);
}

t_bump				char_to_bump(char *str)
{
	if (!ft_strcmp(str, "B_SINUS"))
		return (B_SINUS);
	return (NO_BUMP);
}

t_texture			char_to_texture(char *str)
{
	if (!ft_strcmp(str, "SINUS"))
		return (SINUS);
	if (!ft_strcmp(str, "SINUS_COSINUS"))
		return (SINUS_COSINUS);
	if (!ft_strcmp(str, "STRIPES"))
		return (STRIPES);
	if (!ft_strcmp(str, "CHECKERBOARD"))
		return (CHECKERBOARD);
	if (!ft_strcmp(str, "WEIGHT_SUM_CHECKERBOARD"))
		return (WEIGHT_SUM_CHECKERBOARD);
	if (!ft_strcmp(str, "PERLIN"))
		return (PERLIN);
	if (!ft_strcmp(str, "FRACTAL_SUM_PERLIN"))
		return (FRACTAL_SUM_PERLIN);
	if (!ft_strcmp(str, "SINUS_SUM_PERLIN"))
		return (SINUS_SUM_PERLIN);
	if (!ft_strcmp(str, "WALL"))
		return (WALL);
	if (!ft_strcmp(str, "MARBLE"))
		return (MARBLE);
	return (NO_TEXT);
}

t_shd				char_to_shd(char *str)
{
	if (!ft_strcmp(str, "PHONG"))
		return (PHONG);
	return (LAMBERT);
}

t_vec3				get_color_from_node(xmlNodePtr node)
{
	t_vec3			new;
	xmlChar			*tmp;

	tmp = ((xmlGetProp(node, BAD_CAST"r")));
	new.x = atof((char *)tmp);
	xmlFree(tmp);
	tmp = ((xmlGetProp(node, BAD_CAST"g")));
	new.y = atof((char *)tmp);
	xmlFree(tmp);
	tmp = ((xmlGetProp(node, BAD_CAST"b")));
	new.z = atof((char *)tmp);
	xmlFree(tmp);
	return (new);
}
