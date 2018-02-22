/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/22 15:32:47 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

int				create_sphere(xmlNodePtr node, t_scene *scn)
{
	t_sphere	sphere;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "radius")))
		sphere.radius = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "scale")))
		sphere.radius *= atof((char *)xmlGetProp(child, BAD_CAST"scale"));
	if ((child = has_child(node, "center")))
		sphere.center = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		sphere.center = ft_obj_translation(child, sphere.center);
	if (!(new = obj_lstnew(SPHERE, &sphere, sizeof(sphere))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_plane(xmlNodePtr node, t_scene *scn)
{
	t_plane		plane;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "p")))
		plane.p = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		plane.p = ft_obj_translation(child, plane.p);
	if ((child = has_child(node, "normal")))
		plane.normal = normalize_vec4(get_vec4_from_node(child));
	if ((child = has_child(node, "rotation")))
		plane.normal = ft_obj_rotation(child, plane.normal);
	if (!(new = obj_lstnew(PLANE, &plane, sizeof(plane))))
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
	t_obj_lst	*new;

	if ((child = has_child(node, "angle")))
		cone.angle = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "scale")))
		cone.angle *= atof((char *)xmlGetProp(child, BAD_CAST"scale"));
	if ((child = has_child(node, "p")))
		cone.p = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		cone.p = ft_obj_translation(child, cone.p);
	if ((child = has_child(node, "dir")))
		cone.dir = get_vec4_from_node(child);
	if ((child = has_child(node, "rotation")))
		cone.dir = ft_obj_rotation(child, cone.dir);
	if (!(new = obj_lstnew(CONE, &cone, sizeof(cone))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_cylinder(xmlNodePtr node, t_scene *scn)
{
	t_cylinder	cyl;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "radius")))
		cyl.radius = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "scale")))
		cyl.radius *= atof((char *)xmlGetProp(child, BAD_CAST"scale"));
	if ((child = has_child(node, "p")))
		cyl.p = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		cyl.p = ft_obj_translation(child, cyl.p);
	if ((child = has_child(node, "dir")))
		cyl.dir = get_vec4_from_node(child);
	if ((child = has_child(node, "rotation")))
		cyl.dir = ft_obj_rotation(child, cyl.dir);
	if (!(new = obj_lstnew(CYLINDER, &cyl, sizeof(cyl))))
		ft_putendl("error\n");
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				get_obj(xmlNodePtr node, t_scene *scn)
{
	if (!xmlStrcmp(node->name, BAD_CAST"sphere"))
		create_sphere(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"plane"))
		create_plane(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"cone"))
		create_cone(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"cylindre"))
		create_cylinder(node, scn);
	return (1);
}
