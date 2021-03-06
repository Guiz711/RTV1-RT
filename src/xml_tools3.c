/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:35:06 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 18:11:03 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

void				free_xml(void **ptr)
{
	if (ptr)
	{
		if (*ptr)
			xmlFree(*ptr);
		*ptr = NULL;
	}
}

void				xml_img_att2(t_scene *scene, xmlNodePtr root, xmlChar *tmp)
{
	tmp = xmlGetProp(root, BAD_CAST"filtre");
	if (tmp == NULL)
		scene->filtre = 0;
	else
	{
		scene->filtre = ft_atoi((char *)tmp);
		if (scene->filtre > 6 || scene->filtre < 1)
			scene->filtre = 0;
		xmlFree(tmp);
	}
}

void				xml_img_att(t_scene *scene, xmlNodePtr root)
{
	xmlChar *tmp;

	tmp = xmlGetProp(root, BAD_CAST"render");
	if (tmp == NULL)
		scene->render_mode = 0;
	else
	{
		scene->render_mode = ft_atoi((char *)tmp);
		if (scene->render_mode > 4 || scene->render_mode < 0)
			scene->render_mode = 0;
		free_xml((void**)&tmp);
	}
	tmp = xmlGetProp(root, BAD_CAST"global_refract");
	if (tmp == NULL)
		scene->filtre = 0;
	else
	{
		scene->refra = ft_atoi((char *)tmp);
		if (scene->refra != 1)
			scene->refra = 1;
		xmlFree(tmp);
	}
	xml_img_att2(scene, root, tmp);
}

t_vec4				get_vec4_from_node(xmlNodePtr node)
{
	t_vec4			new;
	xmlChar			*tmp;

	tmp = ((xmlGetProp(node, BAD_CAST"x")));
	new.x = atof((char *)tmp);
	xmlFree(tmp);
	tmp = ((xmlGetProp(node, BAD_CAST"y")));
	new.y = atof((char *)tmp);
	xmlFree(tmp);
	tmp = ((xmlGetProp(node, BAD_CAST"z")));
	new.z = atof((char *)tmp);
	xmlFree(tmp);
	tmp = ((xmlGetProp(node, BAD_CAST"w")));
	new.w = atof((char *)tmp);
	xmlFree(tmp);
	return (new);
}

int					get_modes_nbr(t_args *args)
{
	int				mode_nbr;

	mode_nbr = sizeof(args->rdr_fct) / 8;
	return (mode_nbr);
}
