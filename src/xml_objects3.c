/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:38:10 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/23 11:25:34 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

int				get_obj(xmlNodePtr node, t_scene *scn)
{
	if (!xmlStrcmp(node->name, BAD_CAST"sphere"))
		if (!(create_sphere(node, scn)))
			return (0);
	if (!xmlStrcmp(node->name, BAD_CAST"plane"))
		if (!(create_plane(node, scn)))
			return (0);
	if (!xmlStrcmp(node->name, BAD_CAST"cone"))
		if (!(create_cone(node, scn)))
			return (0);
	if (!xmlStrcmp(node->name, BAD_CAST"paraboloid"))
		if (!(create_paraboloid(node, scn)))
			return (0);
	if (!xmlStrcmp(node->name, BAD_CAST"cylindre"))
		if (!(create_cylinder(node, scn)))
			return (0);
	if (!xmlStrcmp(node->name, BAD_CAST"triangle"))
		if (!(create_triangle(node, scn)))
			return (0);
	return (1);
}
