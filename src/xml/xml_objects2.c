/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:11:22 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 17:43:29 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

static int		new_paraboloid(xmlNodePtr node, t_scene *scn, t_parab parab)
{
	t_obj_lst	*new;

	if (!(new = obj_lstnew(PARABOLOID, &parab, sizeof(parab))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_paraboloid(xmlNodePtr node, t_scene *scn)
{
	t_parab		parab;
	xmlNodePtr	child;
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
	return (new_paraboloid(node, scn, parab));
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
	triangle.normal = get_triangle_normal(triangle.p1,
		triangle.p2, triangle.p3);
	if (!(new = obj_lstnew(TRIANGLE, &triangle, sizeof(triangle))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

static int		new_cone(xmlNodePtr node, t_scene *scn, t_cone cone)
{
	t_obj_lst	*new;

	if (!(new = obj_lstnew(CONE, &cone, sizeof(cone))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_cone(xmlNodePtr node, t_scene *scn)
{
	t_cone		cone;
	xmlNodePtr	child;
	xmlChar		*tmp;

	if ((child = has_child(node, "angle")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"nb")));
		cone.angle = atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "scale")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"scale")));
		cone.angle *= atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "p")))
		cone.p = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		cone.p = ft_obj_translation(child, cone.p);
	if ((child = has_child(node, "dir")))
		cone.dir = get_vec4_from_node(child);
	if ((child = has_child(node, "rotation")))
		cone.dir = ft_obj_rotation(child, cone.dir);
	return (new_cone(node, scn, cone));
}
