/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/03 05:03:34 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3			get_vec3_from_node(xmlNodePtr node)
{
	t_vec3	new;

	new.x = ft_atoi((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = ft_atoi((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = ft_atoi((char *)(xmlGetProp(node, BAD_CAST"z")));
	return (new);
}

t_vec4			get_vec4_from_node(xmlNodePtr node)
{
	t_vec4	new;

	new.x = ft_atoi((char *)(xmlGetProp(node, BAD_CAST"x")));
	new.y = ft_atoi((char *)(xmlGetProp(node, BAD_CAST"y")));
	new.z = ft_atoi((char *)(xmlGetProp(node, BAD_CAST"z")));
	new.w = 1;
	return (new);
}


int				create_sphere(xmlNodePtr node, t_scene *scn)
{
	t_sphere	sphere;
	xmlChar		*val;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if (val == xmlGetProp(node, BAD_CAST"radius"))
		sphere.radius = ft_atoi((char *)val);
	if ((child = has_child(node, "center")))
		sphere.center = get_vec4_from_node(child);
	new = obj_lstnew(SPHERE, &sphere, sizeof(sphere));
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

int				create_plane(xmlNodePtr node, t_scene *scn)
{
	t_plane		plane;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "point")))
		plane.p = get_vec4_from_node(child);
	if ((child = has_child(node, "normal")))
		plane.normal = normalize_vec4(get_vec4_from_node(child));
	new = obj_lstnew(PLANE, &plane, sizeof(plane));
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

int				create_cone(xmlNodePtr node, t_scene *scn)
{
	t_cone		cone;
	xmlChar		*val;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((val = xmlGetProp(node, BAD_CAST"angle")))
		cone.angle = ft_atoi((char *)val);
	cone.ang_tan = 1 + SQUARE(tan(RAD(cone.angle * 0.5)));
	if ((child = has_child(node, "point")))
		cone.p = get_vec4_from_node(child);
	if ((child = has_child(node, "dir")))
		cone.dir = get_vec4_from_node(child);
	new = obj_lstnew(CONE, &cone, sizeof(cone));
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
	xmlChar		*val;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((val = xmlGetProp(node, BAD_CAST"radius")))
		cyl.radius = ft_atoi((char *)val);
	if ((child = has_child(node, "point")))
		cyl.p = get_vec4_from_node(child);
	if ((child = has_child(node, "dir")))
		cyl.dir = get_vec4_from_node(child);
	new = obj_lstnew(CYLINDER, &cyl, sizeof(cyl));
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
