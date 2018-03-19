/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 09:33:14 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 17:32:13 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

/*
** xmlReadFile(const char *filename, const char *encoding, int option)
** filename = path, encoding set to NULL.
** options = see xmlParserOption on xmlsoft.org
** return = xmlDocPtr.
** Here the function check if the path lead to an existing file and open it.
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
** Check if the path is truly an xml file and if we can open it
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
** The real Begining of the parsing, the function xmlKeepBlanksDefault set to 0
** have to ignore useless blanks during the parsing if i well understand how
** it works haha.
** In a second time we check the validity of the path/file the user give us.
** xmlDocGetRootElement retrieve the root of the xmlfile.
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
	xml_img_att(scene, root);
	lst = get_objects_nodes(doc);
	set_objs(lst, scene);
	ft_lstfree(&lst);
	get_nodes_by_name(root, "camera", &lst);
	set_camera((xmlNodePtr)(lst->content), scene);
	ft_lstfree(&lst);
	get_nodes_by_name(root, "light", &lst);
	set_lights(lst, scene);
	ft_lstfree(&lst);
	return (1);
}

/*
** For now the idea is to parse and send the content
** of the xml file to the rest of the program if there isn't any error.
** None Witchcraft here haha.
*/

int				xml_parse(char *path, t_scene *scn)
{
	int		fd;

	if ((fd = check_file(path)) != -1)
	{
		if (parsedoc(path, scn) > 0)
		{
			xmlCleanupParser();
			return (1);
		}
	}
	return (0);
}
