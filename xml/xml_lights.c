/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:11:04 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/03 03:29:42 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parse.h"

int				get_lights(xmlNodePtr node, t_scene *scn)
{
	t_light		light;
	xmlChar		*val;
	xmlNodePtr	child;

	if ((val = xmlGetProp(node, BAD_CAST"type")))
		light.type = (char *)val;
	if ((child = has_child(node, "vec")))
		light.vec = ft_normalize(get_vec4_from_node(child));
	obj_lstadd(&(scn->light), obj_lstnew(&light, sizeof(light)));
	return (1);
}

int				set_lights(t_list *lst, t_scene *scn)
{
	int i;

	i = 0;
	if (!lst)
		return (-1);
	while (lst)
	{
		get_lights((xmlNodePtr)lst->content, scn);
		lst = lst->next;
		i++;
	}
	ft_lstfree(&lst);
	return (1);
}
