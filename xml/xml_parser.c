/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 00:34:09 by jgourdin          #+#    #+#             */
/*   Updated: 2018/01/03 05:20:54 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
 * A little recursiv function to get every objects from the file.
 * xmlStrcmp find every nodes which is named "name".
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
 * Here we get objects from the xml file and create a lst for each
 * one.
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

/*
 * xmlReadFile(const char *filename, const char *encoding, int option)
 * filename = path, encoding set to NULL.
 * options = see xmlParserOption on xmlsoft.org
 * return = xmlDocPtr.
 * Here the function check if the path lead to an existing file and open it.
*/

xmlDocPtr		getdoc(char *path)
{
	xmlDocPtr	doc;

	doc = xmlReadFile(path, NULL, 0);
	if (doc == NULL)
	{
		ft_putstr("Wrong file\n");
		return (NULL);
	}
	return (doc);
}

/*
 * Check if the path is truly an xml file and if we can open it
*/

int				check_file(char *path)
{
	int			fd;
	int			size;

	if (!path)
		return (-1);
	size = ft_strlen(path) - ft_strlen(".xml");
	if (!ft_strcmp(".xml", path + size))
	{
		if ((fd = open(path, O_RDONLY)) != -1)
			return (fd);
	}
	return (-1);
}

/*
 * The real Begining of the parsing, the function xmlKeepBlanksDefault set to 0
 * have to ignore useless blanks during the parsing if i well understand how
 * it works haha.
 * In a second time we check the validity of the path/file the user give us.
 * xmlDocGetRootElement retrieve the root of the xmlfile.
*/

int				parsedoc(char *path, t_scene *scene)
{
	xmlDocPtr	doc;
	t_list		*lst;
	xmlNodePtr	root;

	xmlKeepBlanksDefault(0);
	if (!(doc = getdoc(path)) || !check_valid(doc))
		return (0);
	if (!(root = xmlDocGetRootElement(doc)))
	{
		ft_putstr("Empty document\n");
		return (0);
	}
	lst = get_objects_nodes(doc);
	set_objs(lst, scene);
	ft_lstfree(&lst);
	get_nodes_by_name(root, "camera", &lst);
	set_camera((xmlNodePtr)(lst->content), scene);
	ft_lstfree(&lst);
	get_nodes_by_name(root, "light", &lst);
	set_light(lst, scene);
	return (1);
}

/*
 * For now the idea is to parse and send the content of the xml file to the rest of
 * the program if there isn't any error. None Witchcraft here haha.
*/
int				parse_start(int argc, char **argv, t_scene *scn)
{
	int		fd;
	char	*path;

	if (argc != 1)
	{
		ft_putstr("Usage: ./rtv1 docname\n");
		return (0);
	}
	path = argv[1];
	if ((fd = check_file(path)) != -1)
	{
		if (parsedoc(path, scn) > 0)
			return(1);
	}
	return (0);
}
