/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:41 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/03 02:30:35 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parse.h"

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


int				create_sphere(t_scene *scn, xmlNodePtr node)
{
	t_sphere	sphere;
	xmlChar		*val;
	xmlNodePtr	child;

	if (val == xmlGetProp(node, BAD_CAST"radius"))
		sphere.radius = ft_atoi((char *)val);
	if ((child = has_child(node, "center")))
		sphere.center = get_vec4_from_node(child);
	if ((child = has_child(node, "color")))
		sphere.color = get_vec3_from_node_from_node(child);
	obj_lstadd(&(scn->objs), obj_lstnew(SPHERE, &sphere, sizeof(sphere)));
	return (1);
}

int				create_plane(t_scene *scn, xmlNodePtr node)
{
	t_plane		plane;
	xmlNodePtr	child;

	if ((child = has_child(node, "point")))
		plane.p = get_vec4_from_node(child);
	if ((child = has_child(node, "normal")))
		plane.normal = ft_normalize(get_vec3_from_node(child));
	obj_lstadd(&(scn->objs), obj_lstnew(PLANE, &plane, sizeof(plane)));
	return (1);
}

int				create_cone(t_scene *scn, xmlNodePtr node)
{
	t_cone		cone;
	xmlChar		*val;
	xmlNodePtr	child;

	if ((val = xmlGetProp(node, BAD_CAST"radius"))
		cone.radius = ft_atoi((char *)val);
	if ((child = has_child(node, "point")))
		cone.p = get_vec_from4_node(child);
	if ((child = has_child(node, "dir")))
		cone.dir = get_vec4_from_node(child);
	obj_lstadd(&(scn->objs), obj_lstnew(CONE, &cone, sizeof(cone)));
	return (1);
}
int				create_cylindre(t_scene *scn, xmlNodePtr node)
{
	t_cylindre	cyl;
	xmlChar		*val;
	xmlNodePtr	child;

	if ((val = xmlGetProp(node, BAD_CAST"radius"))
		cyl.radius = ft_atoi((char *)val);
	if ((child = has_child(node, "point")))
		cyl.p = get_vec4_from_node(child);
	if ((child = has_child(node, "dir")))
		cyl.dir = get_vec4_from_node(child);
	obj_lstadd(&(scn->objs), obj_lstnew(CYLINDRE, &cylindre, sizeof(cyl)));
	return (1);
}

int				get_obj(xmlNodePtr node, t_scene *scn)
{
	if (!xmmlStrcmp(node->name, BAD_CAST"sphere"))
		create_sphere(scn, node);
	if (!xmmlStrcmp(node->name, BAD_CAST"plane"))
		create_plane(scn, node);
	if (!xmmlStrcmp(node->name, BAD_CAST"cone"))
		create_cone(scn, node);
	if (!xmmlStrcmp(node->name, BAD_CAST"cylindre"))
		create_cylindre(scn, node);
	parse_obj_node(scn, node);
	return (1);
}

int				set_objs(t_list *lst, t_scene *scn)
{
	int i;

	i = 0;
	if (!lst)
		return (-1);
	while (lst)
	{
		get_obj((xmlNodePtr)lst->content, scn);
		lst = lst->next;
		i++;
	}
	ft_lstfree(&lst);
	return (1);
}
