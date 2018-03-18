/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:21:27 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 18:21:30 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj_lst	*obj_lstnew(t_obj_type type, void const *content, size_t size)
{
	t_obj_lst	*new;

	if (!(new = (t_obj_lst*)malloc(sizeof(*new))))
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
