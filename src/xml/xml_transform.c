/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchet <hbouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:53:46 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 16:02:56 by hbouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

t_vec3			feed_trans(xmlNodePtr node)
{
	t_vec3		pos;
	xmlChar		*tmp;

	tmp = NULL;
	tmp = xmlGetProp(node, BAD_CAST "x");
	pos.x = atof((char *)tmp);
	if (tmp)
		xmlFree(tmp);
	tmp = NULL;
	tmp = xmlGetProp(node, BAD_CAST "y");
	pos.y = atof((char *)tmp);
	if (tmp)
		xmlFree(tmp);
	tmp = NULL;
	tmp = xmlGetProp(node, BAD_CAST "z");
	pos.z = atof((char *)tmp);
	if (tmp)
		xmlFree(tmp);
	return (pos);
}

t_vec4			ft_obj_translation(xmlNodePtr node, t_vec4 ori_pos)
{
	t_vec3		trans_pos;

	trans_pos = feed_trans(node);
	ori_pos = new_coord(ori_pos,
			translate(trans_pos.x, trans_pos.y, trans_pos.z));
	return (ori_pos);
}

t_vec4			ft_obj_rotation(xmlNodePtr node, t_vec4 ori_orient)
{
	t_vec3		trans_orient;

	trans_orient = feed_trans(node);
	ori_orient = new_coord(ori_orient,
			quat_to_mtx(euler_to_quat(trans_orient)));
	return (ori_orient);
}
