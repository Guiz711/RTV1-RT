/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 12:46:43 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 16:58:11 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_GTK_H
#define LIB_GTK_H

#include "rtv1.h"
#include <libft/includes/libft.h>
#include "gtk/gtk.h"

typedef struct		s_gtk_win
{
	GtkWidget		*pwindow;
	GtkWidget		*layout;
}					t_gtk_win;

typedef struct		s_gtk_value
{
	int				width;
	int				height;
}					t_gtk_value;

typedef struct		s_gtk_inp
{
	gint			max_size;
	gint			max_char;
	gchar			*placeholder;
	gchar			*default_value;
}					t_gtk_inp;

typedef struct		s_gtk
{
	t_gtk_win		menu;
	t_gtk_win		options;
	t_gtk_value		values;
}					t_gtk;

#endif
