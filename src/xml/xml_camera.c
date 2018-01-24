/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:34 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/22 12:40:32 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

int				set_camera(xmlNodePtr node, t_scene *scn)
{
	xmlNodePtr	child;

	if ((child = has_child(node, "origin")))
		scn->cam.orig = get_vec4_from_node(child);
	if ((child = has_child(node, "orientation")))
		scn->cam.orient = get_vec4_from_node(child);
	if ((child = has_child(node, "amb_i")))
		scn->amb_i = get_vec3_from_node(child);
	return (1);
}
