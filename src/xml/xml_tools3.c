/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:35:06 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 13:57:02 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

void				xml_img_att(t_scene *scene, xmlNodePtr root)
{
	if (xmlGetProp(root, BAD_CAST"render") == NULL)
		scene->render_mode = 0;
	else
	{
		scene->render_mode = ft_atoi((char *)xmlGetProp(root, BAD_CAST"render"));
		printf("%d\n", scene->render_mode);
		if (scene->render_mode > 6 || scene->render_mode < 0)
			scene->render_mode = 0;
	}
	if (xmlGetProp(root, BAD_CAST"global_refract") == NULL)
		scene->filtre = 0;
	else
	{
		scene->refra = ft_atoi((char *)xmlGetProp(root, BAD_CAST"global_refract"));
		if (scene->refra != 1)
			scene->refra = 1;
	}
	if (xmlGetProp(root, BAD_CAST"filtre") == NULL)
		scene->filtre = 0;
	else
	{
		scene->filtre = ft_atoi((char *)xmlGetProp(root, BAD_CAST"filtre"));
		if (scene->filtre > 6 || scene->filtre < 1)
			scene->filtre = 0;
	}
}

t_vec4				get_vec4_from_node(xmlNodePtr node)
{
	t_vec4			new;

	new.x = atof((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = atof((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = atof((char *)(xmlGetProp(node, BAD_CAST"z")));
	new.w = atof((char *)(xmlGetProp(node, BAD_CAST"w")));
	return (new);
}

int					get_modes_nbr(t_args *args)
{
	int				mode_nbr;

	mode_nbr = sizeof(args->rdr_fct) / 8;
	return (mode_nbr);
}
