/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:51:56 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/20 14:46:55 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

t_lgt_type		char_to_lgt(char *str)
{
	if (!ft_strcmp(str, "POINT"))
		return (POINT);
	else if (!ft_strcmp(str, "DIRECTIONAL"))
		return (DIRECTIONAL);
	return (POINT);
}

int				get_lights(xmlNodePtr node, t_scene *scn)
{
	t_light		light;
	xmlNodePtr	child;
	xmlChar		*tmp;

	tmp = NULL;
	if ((child = has_child(node, "type")))
		tmp = xmlGetProp(child, BAD_CAST"type");
	light.type = char_to_lgt(((char *)tmp));
	free_xml((void**)&tmp);
	if ((child = has_child(node, "vec")))
		light.vec = get_vec4_from_node(child);
	if ((child = has_child(node, "range")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	light.range = ft_atoi((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "diffuse")))
		light.diff_i = get_color_from_node(child);
	if ((child = has_child(node, "spec")))
		light.spec_i = get_color_from_node(child);
	if ((child = has_child(node, "atten")))
		light.atten = get_color_from_node(child);
	ft_lstadd(&scn->light, ft_lstnew(&light, sizeof(light)));
	return (1);
}

int				set_lights(t_list *lst, t_scene *scn)
{
	if (!lst)
		return (-1);
	while (lst)
	{
		get_lights((xmlNodePtr)lst->content, scn);
		lst = lst->next;
	}
	ft_lstfree(&lst);
	return (1);
}
