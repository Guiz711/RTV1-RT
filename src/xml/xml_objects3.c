/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_objects3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:38:10 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 18:16:05 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

int				get_obj(xmlNodePtr node, t_scene *scn)
{
	if (!xmlStrcmp(node->name, BAD_CAST"sphere"))
		create_sphere(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"plane"))
		create_plane(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"cone"))
		create_cone(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"paraboloid"))
		create_paraboloid(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"cylindre"))
		create_cylinder(node, scn);
	if (!xmlStrcmp(node->name, BAD_CAST"triangle"))
		create_triangle(node, scn);
	return (1);
}
