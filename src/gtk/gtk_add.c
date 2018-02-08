/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:15:55 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 18:21:01 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_add_width(GtkEntry *entry, t_gtk *env)
{
	int			val;

	if ((val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)))) > 2)
		env->values.width = val;
}

void			ft_add_height(GtkEntry *entry, t_gt *env)
{
	int			val;
	if ((val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)))) > 2)
		env->values.height = val;
}
