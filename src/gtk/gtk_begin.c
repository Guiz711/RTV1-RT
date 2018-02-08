/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:01:26 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 17:34:14 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_gtk.h"

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

void			gtk_starting()
{
	t_gtk	env;

	gtk_init(NULL, NULL);
	env->menu.pwindow = gtk_init_win(300, 300, "RTV1");
	env->menu.layout = gtk_init_layout(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(env->menu.pwindow), env-menu.layout);
	g_signal_connect(G_OBJECT(env->menu.pwindow), "delete-event", G_CALLBACk(exit), NULL);
	ft_starting_values(env);
	ft_gtk_factory(env);
	gtk_widget_show_all(env->menu.pwindow);
	g_signal_connect(G_OBJECT(env->menu.pwindow), "event", G_CALLBACK(inexisting_hook), NULL);
	gtk_main();
}
