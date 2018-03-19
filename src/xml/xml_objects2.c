/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:55:04 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 10:36:18 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

int				create_paraboloid(xmlNodePtr node, t_scene *scn)
{
	t_parab		parab;
	xmlNodePtr	child;
	t_obj_lst	*new;
	xmlChar		*tmp;
	if ((child = has_child(node, "k")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"nb")));
		parab.k = atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "scale")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"scale")));
		parab.k *= atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "p")))
		parab.p = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		parab.p = ft_obj_translation(child, parab.p);
	if ((child = has_child(node, "dir")))
		parab.dir = normalize_vec4(get_vec4_from_node(child));
	if ((child = has_child(node, "rotation")))
		parab.dir = ft_obj_rotation(child, parab.dir);
	if (!(new = obj_lstnew(PARABOLOID, &parab, sizeof(parab))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_triangle(xmlNodePtr node, t_scene *scn)
{
	t_triangle	triangle;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "p1")))
		triangle.p1 = get_vec4_from_node(child);
	if ((child = has_child(node, "p2")))
		triangle.p2 = get_vec4_from_node(child);
	if ((child = has_child(node, "p3")))
		triangle.p3 = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
	{
		triangle.p1 = ft_obj_translation(child, triangle.p1);
		triangle.p2 = ft_obj_translation(child, triangle.p2);
		triangle.p3 = ft_obj_translation(child, triangle.p3);
	}
	//if ((child = has_child(node, "rotation")))
	//	rotation des 3 points autour de leur centre
	triangle.normal = get_triangle_normal(triangle.p1, triangle.p2, triangle.p3);//triangle.normal = normalize_vec4(get_vec4_from_node(child));
	if (!(new = obj_lstnew(TRIANGLE, &triangle, sizeof(triangle))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}