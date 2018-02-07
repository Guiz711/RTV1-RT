/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:11:26 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 18:19:04 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * Even if we have a menu window. I think it is wiser to use
 * more window to display the settings, scene and objects.
*/

GtkWidget		*ft_new_win(gint h, gint w, gchar *name)
{
	GtkWidget	*pwin;

	pwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pwin), name);
	gtk_window_set_default_size(GTK_WINDOW(pwin), w, h);
	gtk_window_set_resizable(pwin, FALSE);
	gtk_window_set_position(GTK_WINDOW(pwin), GTK_WIN_POS_CENTER);
	return (pwin);
}

/*
 * to add a new input widget.
 * placeholder is where the user can enter things.
 * gtk_entry_set_text is the default value in the input widget.
*/

GtkWidget		*ft_new_input(t_gtk_inp *data)
{
	GtkWidget	*input;

	input = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input), data->max_size);
	gtk_entry_set_width_chars(GTK_ENTRY(input), data->max_char);
	gtk_entry_set_placeholder_text(GTK_ENTRY(input), data->placeholder);
	gtk_entry_set_text(GTK_ENTRY(input), data->default_value);
	return (input);
}

/*
 * gtk_button_new_with_label create a GtkButton with a GtkLabel child containing
 * the text or here the name. A GtkLabel is a widget that display a small amount
 * of text.
 * gtk_widget_set_size_request, set the size of the widget as you can easily imagine.
 * that all haha !
*/

GtkWidget		*ft_new_button(int x, int y, char *name)
{
	GtkWidget	*button;
	button = gtk_button_new_with_label(name);
	gtk_widget_set_size_request(btn, x, y);
	return(button);
}

/*
 * This function create a new label, a new text.
 *
*/

GtkWidget		*ft_new_label(gchar *str)
{
	GtkWidget *label = NULL;
	label = gtk_label_new(str);
	return (label);
}


