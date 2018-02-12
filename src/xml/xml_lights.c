/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:51:56 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/12 16:52:21 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
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

	if ((child = has_child(node, "type")))
		light.type = char_to_lgt(((char *)xmlGetProp(child, BAD_CAST"type")));
	if ((child = has_child(node, "vec")))
		light.vec = get_vec4_from_node(child);
	if ((child = has_child(node, "range")))
		light.range = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
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
