/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:11:04 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/03 05:13:24 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				get_lights(xmlNodePtr node, t_scene *scn)
{
	t_light		light;
	xmlChar		*val;
	xmlNodePtr	child;

	if ((val = xmlGetProp(node, BAD_CAST"type")))
		light.type = (char *)val;
	if ((child = has_child(node, "vec")))
		light.vec = get_vec4_from_node(child);
	if ((child = has_child(node, "range")))
		light.range = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "diff")))
		light.diff_i = get_vec3_from_node(child);
	if ((child = has_child(node, "spec")))
		light.spec_i = get_vec3_from_node(child);
	if ((child = has_child(node, "atten")))
		light.atten = get_vec3_from_node(child);
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
