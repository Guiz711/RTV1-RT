/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 03:11:12 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/22 11:59:44 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

void			shd_scene(int *shd_arr, char *string)
{
	char		**db;
	int			i;
	int			p;

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

t_bump			char_to_bump(char *str)
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
	return (NO_TEXT);
}

t_shd			char_to_shd(char *str)
{
	if (!ft_strcmp(str, "PHONG"))
		return (PHONG);
	return (LAMBERT);
}

t_vec3			get_color_from_node(xmlNodePtr node)
{
	t_vec3		new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"r")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"g")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"b")));
	return (new);
}

t_vec4			get_vec4_from_node(xmlNodePtr node)
{
	t_vec4		new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"z")));
	new.w = atof((char *)(xmlGetProp(node, BAD_CAST"w")));
	return (new);
}

int				get_modes_nbr(t_args *args)
{
	int			mode_nbr;

	mode_nbr = sizeof(args->rdr_fct) / 8;
	return (mode_nbr);
}
