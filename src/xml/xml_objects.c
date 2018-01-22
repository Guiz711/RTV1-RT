/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/22 03:14:28 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				create_sphere(xmlNodePtr node, t_scene *scn)
{
	t_sphere	sphere;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "radius")))
		sphere.radius = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "center")))
		sphere.center = get_vec4_from_node(child);
	new = obj_lstnew(SPHERE, &sphere, sizeof(sphere));
	if ((child = has_child(node, "model")))
		new->material.model = char_to_shd(((char *)xmlGetProp(child, BAD_CAST"model")));
	if ((child = has_child(node, "amb")))
		new->material.amb = get_vec3_from_node(child);
	if ((child = has_child(node, "diffuse")))
		new->material.diff = get_vec3_from_node(child);
	if ((child = has_child(node, "spec")))
		new->material.spec = get_vec3_from_node(child);
	if ((child = has_child(node, "shininess")))
		new->material.shin = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
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
	if ((child = has_child(node, "normal")))
		plane.normal = normalize_vec4(get_vec4_from_node(child));
	new = obj_lstnew(PLANE, &plane, sizeof(plane));
	if ((child = has_child(node, "model")))
		new->material.model = char_to_shd(((char *)xmlGetProp(child, BAD_CAST"model")));
	if ((child = has_child(node, "amb")))
		new->material.amb = get_vec3_from_node(child);
	if ((child = has_child(node, "spec")))
		new->material.spec = get_vec3_from_node(child);
	if ((child = has_child(node, "diffuse")))
		new->material.diff = get_vec3_from_node(child);
	if ((child = has_child(node, "shininess")))
		new->material.shin = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
	obj_lstadd(&(scn->objs), new);
	return (1);
}

int				create_cone(xmlNodePtr node, t_scene *scn)
{
	t_cone		cone;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node,"angle")))
		cone.angle = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	cone.ang_tan = 1 + SQUARE(tan(RAD(cone.angle * 0.5)));
	if ((child = has_child(node, "p")))
		cone.p = get_vec4_from_node(child);
	if ((child = has_child(node, "dir")))
		cone.dir = get_vec4_from_node(child);
	new = obj_lstnew(CONE, &cone, sizeof(cone));
	if ((child = has_child(node, "model")))
		new->material.model = char_to_shd(((char *)xmlGetProp(child, BAD_CAST"model")));
	if ((child = has_child(node, "diffuse")))
		new->material.diff = get_vec3_from_node(child);
	if ((child = has_child(node, "spec")))
		new->material.spec = get_vec3_from_node(child);
	if ((child = has_child(node, "amb")))
		new->material.amb = get_vec3_from_node(child);
	if ((child = has_child(node, "shininess")))
		new->material.shin = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
	obj_lstadd(&(scn->objs), new);

	return (1);
}

int				create_cylinder(xmlNodePtr node, t_scene *scn)
{
	t_cylinder	cyl;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node,"radius")))
		cyl.radius = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "p")))
		cyl.p = get_vec4_from_node(child);
	if ((child = has_child(node, "dir")))
		cyl.dir = get_vec4_from_node(child);
	new = obj_lstnew(CYLINDER, &cyl, sizeof(cyl));
	if ((child = has_child(node, "model")))
	new->material.model = char_to_shd(((char *)xmlGetProp(child, BAD_CAST"model")));
	if ((child = has_child(node, "diffuse")))
		new->material.diff = get_vec3_from_node(child);
	if ((child = has_child(node, "spec")))
		new->material.spec = get_vec3_from_node(child);
	if ((child = has_child(node, "amb")))
		new->material.amb = get_vec3_from_node(child);
	if ((child = has_child(node, "shininess")))
		new->material.shin = ft_atoi((char *)xmlGetProp(child, BAD_CAST"nb"));
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

int				set_objs(t_list *lst, t_scene *scn)
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
