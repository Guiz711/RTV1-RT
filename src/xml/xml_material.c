/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:03:28 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/15 02:15:42 by jgourdin         ###   ########.fr       */
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
	/*if ((child = has_child(node, "reflet")))
		material.refl = get_color_from_node(child);
	if ((child = has_child(node, "indice_refraction")))
		material.i_refr = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
if ((child = has_child(node, "indice_reflection")))
		material.i_refl = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "light_absorb")))
		material.l_abs = get_color_from_node(child);
	material.transp = (child = has_child(node, "transparent") ? 1 : 0);
		material.l_abs = get_color_from_node(child);
*/
	return (material);

}

int			set_objs(t_list *lst, t_scene *scn)
{
	if (!lst)
		return (-1);
	while (lst)
	{
		get_obj((xmlNodePtr)lst->content, scn);
		lst = lst->next;
	}
	ft_lstfree(&lst);
	return (1);
}
