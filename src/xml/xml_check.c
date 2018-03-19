/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 03:07:36 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 17:17:16 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xml_parser.h"

/*
** Pretty much the same method than parsing the xsd file, even if here
** we need less functions.
** * * * * * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * *
** xmlParseDTD, parse the dtd and stock information in the struct xmlDtdPtr.
** xmlNewValidCtxt, allocate a validation context structure.
** xmlValidateDtd, try to validate the xml file following "rules" from dtd file.
*/

int				dtd_validate(char *path, xmlDocPtr doc)
{
	int				ret;
	xmlDtdPtr		dtd;
	xmlValidCtxtPtr	vctxt;

	if ((dtd = xmlParseDTD(NULL, (xmlChar*)path)) == NULL)
		dtd_error(dtd);
	if ((vctxt = xmlNewValidCtxt()) == NULL)
		xml_alloc_error();
	vctxt->userData = (void *)stderr;
	vctxt->error = (xmlValidityErrorFunc)NULL;
	vctxt->warning = (xmlValidityWarningFunc)NULL;
	ret = xmlValidateDtd(vctxt, doc, dtd);
	xmlFreeValidCtxt(vctxt);
	xmlFreeDtd(dtd);
	return (ret);
}

/*
** Here we create the right struct to parse the xml schema file.
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** xmlSchemaNewParserCtxt, create a parsong context structur.
** xmlSchemaParse, create a structure that will be used to validate xml file.
*/

/*
** Here we check if our xml file and xsd (schema xml) file are valid.
** ctxt structures are validations structures, they stock information
** about the validation or not of our files.
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** xmlSchemaNewValidCtxt, create the context of the xml validation struct.
** xmlSchemaSetValidErrors, set the options to be used during validation.
** xmlSchemaValidateDoc, validate or not the xml file.
*/

/*
** The xml file need to fit in the form set in two validations files.
** First we check if in themselves validations are valid.
** If it's ok for both, we can let the parser make his job
** otherwise we print where it failed.
*/

int				check_valid(xmlDocPtr doc)
{
	xmlValidCtxtPtr	vctxt;
	int				dtd;

	if (!(vctxt = xmlNewValidCtxt()))
		return (0);
	if (!(dtd = dtd_validate("validator.dtd", doc)))
	{
		xmlFreeValidCtxt(vctxt);
		return (0);
	}
	xmlFreeValidCtxt(vctxt);
	return (1);
}
