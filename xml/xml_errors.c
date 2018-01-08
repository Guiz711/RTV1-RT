/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 05:59:23 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/30 06:09:38 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/valid.h>
#include <libxml/tree.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlstring.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/includes/libft.h"

/*
 * Clean up the memory allocated by the libxml with CleanupParser.
*/

int		xsd_error(void)
{
	ft_putstr("Problems with XML Schema\n");
	xmlCleanupParser();
	exit(-1);
}

int		dtd_error(xmlDtdPtr dtd)
{
	ft_putstr("Wrong xml file\n");
	xmlFreeDtd(dtd);
	exit(-1);
}

int		alloc_error(void)
{
	ft_putstr("Error happened\n");
	exit(-1);
}
int		xml_error(void)
{
	ft_putstr("Wrong xml file\n");
	exit(-1);
}
