/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_material.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:35:28 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 17:10:55 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

static t_mat	xml_material3(xmlNodePtr node, t_mat material, xmlNodePtr child)
{
	xmlChar		*tmp;

	tmp = NULL;
	if ((child = has_child(node, "model")))
		tmp = xmlGetProp(child, BAD_CAST"model");
	material.model = char_to_shd((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "refract")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.refract = atof((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "reflect")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.reflect = atof((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "opacity")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.opacity = atof((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "text_angle")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.text_angle = atof((char *)tmp);
	free_xml((void**)&tmp);
	return (material);
}

t_mat			xml_material2(xmlNodePtr node, t_mat material, xmlNodePtr child)
{
	xmlChar		*tmp;

	tmp = NULL;
	if ((child = has_child(node, "texture")))
		tmp = xmlGetProp(child, BAD_CAST"texture");
	material.texture = char_to_texture((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "amb")))
		material.amb = get_color_from_node(child);
	if ((child = has_child(node, "diffuse")))
		material.diff = get_color_from_node(child);
	if ((child = has_child(node, "spec")))
		material.spec = get_color_from_node(child);
	if ((child = has_child(node, "shininess")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.shin = ft_atoi((char *)tmp);
	free_xml((void**)&tmp);
	if (material.texture == PERLIN || material.texture == FRACTAL_SUM_PERLIN
		|| material.texture == SINUS_SUM_PERLIN)
		fill_text_map(&material);
	material = xml_material3(node, material, child);
	return (material);
}

t_mat			xml_parse_material(xmlNodePtr node)
{
	t_mat		material;
	xmlNodePtr	child;
	xmlChar		*tmp;

	tmp = NULL;
	if ((child = has_child(node, "text_scale")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.text_scale = atof((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "bump_text")))
		tmp = xmlGetProp(child, BAD_CAST"bump_text");
	material.bump_text = char_to_bump((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "bump_angle")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.bump_angle = atof((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "bump_scale")))
		tmp = xmlGetProp(child, BAD_CAST"nb");
	material.bump_scale = atof((char *)tmp);
	free_xml((void**)&tmp);
	if ((child = has_child(node, "absorb")))
		material.absorb = get_color_from_node(child);
	material = xml_material2(node, material, child);
	return (material);
}

int				set_objs(t_list *lst, t_scene *scn)
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
