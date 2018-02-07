/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:24:16 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 18:12:37 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
 * Here we're going to display some label, to indicate what are
 * each widget. And obviously the update button to redraw the RT and apply changes. We only have the ScreenSize for now to display
 * but i think it's a good start haha !
*/

void			ft_display_info(t_gtk *env)
{
	gtk_layout_put(GTK_LAYOUT(env->options.layout), new_label("Screen size"), 20, 20);
	gtk_widget_show_all(env->options.pwindow);
	ft_display_win_size(env);
	ft_diplay_update(env);
	g_signal_connect(env->options.pwindow, "delete-event", G_CALLBACK(close_options), env);
}

/*
 * This function have to display the size of the RT window and allow the user to
 * modify it. First we put a maximum to the value even if later we are going to 
 * verify if the value is way too big or too small (2 and the max size of the window but
 * we have to verify this i don't think it's the good value).
 * After that we save the actual size in default_value.
 * We take a new entry with our ft_new_input.
 * And we put the values if the user use the widget.
*/

void			ft_display_winsize(t_gtk *env)
{
	t_gtk_inp	input;
	GtkWidget	*width;
	GtkWidget	*height;

	input.max_char = 5;
	input.max_size = 5;
	input.placeholder = "width";
	input.default_value = ft_itoa(WIN_WIDTH);
	width = ft_new_input(&input);
	input.placeholder = "height";
	input.default_value = ft_itoa(WIN_HEIGHT);
	height = new_input(&input);
	gtk_layout_put(GTK_LAYOUT(env->options.layout), width, 20, 40);
	gtk_layout_put(GTK_LAYOUT(env->options.layout), width, 80, 40);
	g_signal_connect(width, "activate", G_CALLBACK(ft_add_width), env);
	g_signal_connect(width, "activate", G_CALLBACK(ft_add_height), env);
}

/*
 * The famous display button
 * Add a new button UPDATE that will apply modifications.
*/

void			ft_display_update(t_gtk *env)
{
	GtkWidget	*btn;

	btn = ft_button(100, 40, "UPDATE");
	gtk_layout_put(GTK_LAYOUT(env->options.layout), btn, 50, 250);
	g_signal_connect(btn, "clicked", G_CALLBACK(ft_update), env);
}

