/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:34 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/09 18:05:37 by jgourdin         ###   ########.fr       */
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
		scn->amb_i = get_color_from_node(child);
	return (1);
}
