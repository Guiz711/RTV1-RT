/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:08:26 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/23 11:48:12 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"
#include "rtv1.h"

static int		new_sphere(xmlNodePtr node, t_scene *scn, t_sphere sphere)
{
	t_obj_lst	*new;

	if (!(new = obj_lstnew(SPHERE, &sphere, sizeof(sphere))))
	{
		ft_putendl("error\n");
		return (0);
	}
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_sphere(xmlNodePtr node, t_scene *scn)
{
	t_sphere	sphere;
	xmlNodePtr	child;
	xmlChar		*tmp;

	if ((child = has_child(node, "radius")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"nb")));
		sphere.radius = atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "scale")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"scale")));
		sphere.radius *= atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "center")))
		sphere.center = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		sphere.center = ft_obj_translation(child, sphere.center);
	return (new_sphere(node, scn, sphere));
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
	{
		ft_putendl("error\n");
		return (0);
	}
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

static int		new_cylinder(xmlNodePtr node, t_scene *scn, t_cylinder cyl)
{
	t_obj_lst	*new;

	if (!(new = obj_lstnew(CYLINDER, &cyl, sizeof(cyl))))
	{
		ft_putendl("error\n");
		return (0);
	}
	new->material = xml_parse_material(node);
	new->id_obj = scn->nb_obj;
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_cylinder(xmlNodePtr node, t_scene *scn)
{
	t_cylinder	cyl;
	xmlNodePtr	child;
	xmlChar		*tmp;

	if ((child = has_child(node, "radius")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"nb")));
		cyl.radius = atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "scale")))
	{
		tmp = ((xmlGetProp(child, BAD_CAST"scale")));
		cyl.radius *= atof((char *)tmp);
		free_xml((void**)&tmp);
	}
	if ((child = has_child(node, "p")))
		cyl.p = get_vec4_from_node(child);
	if ((child = has_child(node, "translation")))
		cyl.p = ft_obj_translation(child, cyl.p);
	if ((child = has_child(node, "dir")))
		cyl.dir = get_vec4_from_node(child);
	if ((child = has_child(node, "rotation")))
		cyl.dir = ft_obj_rotation(child, cyl.dir);
	return (new_cylinder(node, scn, cyl));
}
