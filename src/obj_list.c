/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 21:01:12 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/08 10:54:06 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj_lst	*obj_lstnew(t_obj_type type, void const *content, size_t size)
{
	t_obj_lst	*new;

	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = malloc(size)))
		{
			free(new);
			return (NULL);
		}
		ft_memcpy(new->content, content, size);
		new->content_size = size;
		new->content_type = type;
	}
	new->next = NULL;
	return (new);
}

void		obj_lstadd(t_obj_lst **alst, t_obj_lst *new)
{
	if (alst)
	{
		new->next = *alst;
		*alst = new;
	}
}