/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2_xml.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 03:11:12 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/22 03:16:44 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				shd_scene(int *shd_arr, char *string)
{
	char **db = NULL;
	int i = -1;
	int p = -1;

	db = ft_strsplit(string, '|');
	while (db[++i])
	{
		if (ft_strcmp(db[i], "NO_SHD") == 0)
			p = NO_SHD;
		else if (ft_strcmp(db[i], "FACING") == 0)
			p = FACING;
		else if (ft_strcmp(db[i], "SHADOW") == 0)
			p = SHADOW;
		else if (ft_strcmp(db[i], "LAMBERT") == 0)
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

t_shd				char_to_shd(char *str)
{
	if (!ft_strcmp(str, "PHONG"))
		return (PHONG);
	return (NO_SHD);
}
t_vec3			get_vec3_from_node(xmlNodePtr node)
{
	t_vec3	new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"z")));
	return (new);
}

t_vec4			get_vec4_from_node(xmlNodePtr node)
{
	t_vec4	new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"z")));
	new.w = atof((char *)(xmlGetProp(node, BAD_CAST"w")));
	return (new);
}

