/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:06:29 by hbouchet          #+#    #+#             */
/*   Updated: 2018/03/19 17:06:30 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

int				set_camera(xmlNodePtr node, t_scene *scn)
{
	xmlNodePtr	child;

	if ((child = has_child(node, "origin")))
		scn->cam.orig = get_vec4_from_node(child);
	if ((child = has_child(node, "orientation")))
		scn->cam.orient = get_vec4_from_node(child);
	if ((child = has_child(node, "amb_i")))
		scn->amb_i = get_color_from_node(child);
	return (1);
}
