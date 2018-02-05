/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:01:26 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/05 16:59:58 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gtk.h"

void		quit(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

/*
 * gtk_button_new_with_label create a GtkButton with a GtkLabel child containing
 * the text or here the name. A GtkLabel is a widget that display a small amount
 * of text.
 * gtk_widget_set_size_request, set the size of the widget as you can easily imagine.
 * that all haha !
*/

GtkWidget		*ft_button(int x, int y, char *name)
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

GtkWidget		*new_label(gchar *str)
{
	GtkWidget *label = NULL;
	label = gtk_label_new(str);
	return (label);
}

GtkWidget		*gtk_init_win(gint h, gint w, gchar *name)
{
	GtkWidget	*pwin;

	pwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pwin), name);
	gtk_window_set_default_size(GTK_WINDOW(pwin), w, h);
	gtk_window_set_resizable(pwin, FALSE);
	gtk_window_set_position(GTK_WINDOW(pwin), GTK_WIN_POS_CENTER);
	return (pwin);
}

void			ft_feed_gtk(t_gtk *env)
{
	env->values.width = WIN_WIDTH;
	env->values.height = WIN_HEIGHT;
}

void			ft_add_w(GtkEntry *entry, t_gtk *env)
{
	int			val;

	if ((val = ft_atoi(gtk_entry_get_text(GTK_ENTRY(entry)))) > 2)
		env->values.width = val;
}

GtkWidget		*new_input(t_gtk_inp *data)
{
	GtkWidget	*input;

	input = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(input), data->max_size);
	gtk_entry_set_width_chars(GTK_ENTRY(input), data->max_char);
	gtk_entry_set_placeholder_text(GTK_ENTRY(input), data->placeholder);
	gtk_entry_set_text(GTK_ENTRY(input), data->default_value);
	return (input);
}

void			ft_display_win_size(t_gtk *env)
{
	t_gtk_inp	input;
	GtkWidget	*width;
	//GtkWidget	*height;

	input.max_char = 5;
	input.max_size = 5;
	input.placeholder = "width";
	input.default_value = ft_itoa(WIN_WIDTH);
	width = new_input(&input);
	gtk_layout_put(GTK_LAYOUT(env->options.layout), width, 20, 40);
	g_signal_connect(width, "activate", G_CALLBACK(ft_add_w), env);
}

void			ft_update(GtkButton *btn, t_gtk *env)
{
	gtk_widget_destroy(env->settings.pwindow);
	WIN_WIDTH = env->values.width > 2560 ? 2560 : env->values.width;
	WIN_HEIGHT = env->values.height > 1440 ? 1440 : env->values.height;
	trace_primary_rays(env);
}

void			ft_display_update(t_gtk *env)
{
	GtkWidget	*btn;

	btn = ft_button(100, 40, "UPDATE");
	gtk_layout_put(GTK_LAYOUT(env->options.layout), btn, 50, 250);
	g_signal_connect(btn, "clicked", G_CALLBACK(ft_update), env);
}

void			ft_display_info(t_gtk *env)
{
	gtk_layout_put(GTK_LAYOUT(env->options.layout), new_label("Screen size"), 20, 20);
	gtk_widget_show_all(env->options.pwindow);
	ft_display_win_size(env);
	ft_diplay_update(env);
	g_signal_connect(env->options.pwindow, "delete-event", G_CALLBACK(close_options), env);
}

/* So, here a lot of information... Stay alive haha it isn't seems to be really
 * hard to understand (but i just begin who knows).
 * so So SO gtk_init do what you expect him to do, if you lauch gtk in the main give him
 * argc and argv, otherwise NULL and NULL. You don't have to end gtk <3 .
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gtk_window_new DO WHAT YOU EXPECT HIM TO DOOO, isn't it beautiful ? we should give
 * him the type of window, justst like a SDL WINDOW. The documentation say that often
 * we just have to give him GTK_WINDOW_TOPLEVEL for a regulat window as a dialog.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gtk_widget_show_all display all widget wich are in my window.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * g_signal_connect have to manage events, i give him the instance, the detailed signal (???) the GCallback and the data (??? i give him NULL here).
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gtk_layout_new allow an infinit scrollable area.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

void			gtk_starting(t_gtk *env)
{
	gtk_init(NULL, NULL);
	env->menu.pwindow = gtk_init_win(300, 300, "RT");
	env->menu.layout = gtk_init_layout(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(env->menu.pwindow), env-menu.layout);
	g_signal_connect(G_OBJECT(env->menu.pwindow), "delete-event", G_CALLBACk(quit), NULL);
	ft_feed_gtk(env);
	gtk_widget_show_all(env->menu.pwindow);
	gtk_main();
}
