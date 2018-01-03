/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 06:12:34 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/03 02:40:29 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				set_camera(xmlNodePtr node, t_scene *scn)
{
	xmlNodePtr	child;
	xmlChar		*val;

	if ((child = has_child(node, "origin")))
		scn->cam.origin = get_vec4_from_node(node);
	if ((child = has_child(node, "orientation")))
		scn->cam.orient = get_vec4_from_node(node);
	return (1);
}
