/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_xml.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 03:08:20 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/12 16:53:30 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

xmlNodePtr		has_child(xmlNodePtr a_node, char *attr)
{
	xmlChar		*cast;
	xmlNodePtr	cur;

	cur = NULL;
	cur = a_node->children;
	cast = (xmlChar *)attr;
	while (cur)
	{
		if (!xmlStrcmp(cur->name, cast))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void			ft_lstfree(t_list **lst)
{
	if (*lst)
	{
		ft_lstfree(&((*lst)->next));
		free(*lst);
		*lst = NULL;
	}
}

void			ft_lstpush(t_list **alst, t_list *new)
{
	t_list	*tmp;

	new->next = NULL;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/*
** A little recursiv function to get every objects from the file.
** xmlStrcmp find every nodes which is named "name".
*/

void			get_nodes_by_name(xmlNodePtr cur, char *name, t_list **lst)
{
	t_list		*new;

	while (cur)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)name)))
		{
			new = ft_lstnew((void *)cur, sizeof(*cur));
			ft_lstpush(lst, new);
		}
		get_nodes_by_name(cur->children, name, lst);
		cur = cur->next;
	}
}

/*
** Here we get objects from the xml file and create a lst for each
** one.
*/

t_list			*get_objects_nodes(xmlDocPtr doc)
{
	t_list		*lst;
	t_list		*lst2;
	t_list		*new;
	xmlNodePtr	tmp;

	if (!doc)
		return (NULL);
	lst = NULL;
	lst2 = NULL;
	tmp = NULL;
	get_nodes_by_name(xmlDocGetRootElement(doc), "objects", &lst);
	if (!lst)
		return (NULL);
	tmp = ((xmlNodePtr)lst->content)->children;
	while (tmp)
	{
		new = ft_lstnew((void *)tmp, sizeof(*tmp));
		ft_lstpush(&lst2, new);
		tmp = tmp->next;
	}
	return (lst2);
}
