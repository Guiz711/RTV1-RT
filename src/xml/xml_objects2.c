/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:55:04 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/16 15:14:33 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				create_paraboloid(xmlNodePtr node, t_scene *scn)
{
	t_parab		parab;
	xmlNodePtr	child;
	t_obj_lst	*new;

	if ((child = has_child(node, "k")))
		parab.k = atof((char *)xmlGetProp(child, BAD_CAST"nb"));
	if ((child = has_child(node, "scale")))
		parab.k *= atof((char *)xmlGetProp(child, BAD_CAST"scale"));
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
