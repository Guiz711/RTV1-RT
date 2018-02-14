/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 17:53:46 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/12 16:42:11 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

t_vec3			feed_trans(xmlNodePtr node)
{
	t_vec3		pos;

	pos.x = atof((char *)(xmlGetProp(node, BAD_CAST "x")));
	pos.y = atof((char *)(xmlGetProp(node, BAD_CAST "y")));
	pos.z = atof((char *)(xmlGetProp(node, BAD_CAST "z")));
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
