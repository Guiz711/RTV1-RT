/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 09:45:29 by gmichaud          #+#    #+#             */
/*   Updated: 2018/01/22 03:18:37 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "rtv1.h"
#include "../libxml/xmlmemory.h"
#include "../libxml/parser.h"
#include "../libxml/tree.h"
#include "../libxml/xmlIO.h"
#include "../libxml/xinclude.h"
#include "../libxml/valid.h"
#include "../libxml/xmlschemas.h"
#include "../libxml/xmlstring.h"
#include "../libxml/xmlreader.h"

t_shd			char_to_shd(char *str);
int			xml_parse(char *path, t_scene *scn);
int			set_objs(t_list *lst, t_scene *scn);
int			set_lights(t_list *lst, t_scene *scn);
int			set_camera(xmlNodePtr node, t_scene *scn);
t_vec3		get_vec3_from_node(xmlNodePtr node);
t_vec4		get_vec4_from_node(xmlNodePtr node);
int			xsd_error(void);
int			dtd_error(xmlDtdPtr dtd);
int			xml_alloc_error(void);
int			xml_error(void);
int			check_valid(xmlDocPtr doc);
void		ft_lstfree(t_list **lst);
void		ft_lstpush(t_list **alst, t_list *new);
void		get_nodes_by_name(xmlNodePtr cur, char *name, t_list **lst);
xmlNodePtr	has_child(xmlNodePtr a_node, char *attr);
void		shd_scene(int *shd_arr, char *string);
t_list		*get_objects_nodes(xmlDocPtr doc);


#endif
