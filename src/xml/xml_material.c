/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:03:28 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/15 13:43:45 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

t_mat		xml_parse_material(xmlNodePtr node)
{
	t_mat		material;
	xmlNodePtr	child;

	if ((child = has_child(node, "model")))
		material.model =
			char_to_shd(((char *)xmlGetProp(child, BAD_CAST"model")));
	if ((child = has_child(node, "amb")))
		material.amb = get_color_from_node(child);
	if ((child = has_child(node, "diffuse")))
		material.diff = get_color_from_node(child);
	if ((child = has_child(node, "spec")))
		material.spec = get_color_from_node(child);
	if ((child = has_child(node, "shininess")))
		material.shin = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "refract")))
		material.refract = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "reflect")))
		material.reflect = get_color_from_node(child);
	if ((child = has_child(node, "transparency")))
		material.transparency = 1;
	else
		material.transparency = 0;
// */
	return (material);

}

int			set_objs(t_list *lst, t_scene *scn)
{
	scn->nb_obj = 0;
	if (!lst)
		return (-1);
	while (lst)
	{
		scn->nb_obj++;
		get_obj((xmlNodePtr)lst->content, scn);
		lst = lst->next;
	}
	ft_lstfree(&lst);
	return (1);
}
