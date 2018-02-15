/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:03:28 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/15 09:25:16 by jgourdin         ###   ########.fr       */
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
	if ((child = has_child(node, "i_refr")))
		material.i_refr = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "i_refl")))
		material.i_refl = get_color_from_node(child);
	if ((child = has_child(node, "transp")))
		material.transp = 1;
	else
		material.transp = 0;
*/
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
