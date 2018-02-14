/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 05:59:23 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/12 16:52:48 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "xml_parser.h"

/*
** Clean up the memory allocated by the libxml with CleanupParser.
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

int		xml_alloc_error(void)
{
	ft_putstr("Error happened\n");
	exit(-1);
}

int		xml_error(void)
{
	ft_putstr("Wrong xml file\n");
	exit(-1);
}
