/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 13:03:28 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/22 15:33:52 by gmichaud         ###   ########.fr       */
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
	if ((child = has_child(node, "texture")))
		material.texture =
			char_to_texture(((char *)xmlGetProp(child, BAD_CAST"texture")));
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
		material.reflect = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "opacity")))
		material.opacity = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "text_angle")))
		material.text_angle = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "text_scale")))
		material.text_scale = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "bump_text")))
		material.bump_text =
			char_to_bump(((char *)xmlGetProp(child, BAD_CAST"bump_text")));
	if ((child = has_child(node, "bump_angle")))
		material.bump_angle = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "bump_scale")))
		material.bump_scale = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "absorb")))
		material.absorb = get_color_from_node(child);


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
