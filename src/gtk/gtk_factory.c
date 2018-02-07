/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:09:54 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 18:21:03 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
 * In order to have an idea of the actual size of the window
*/

void			ft_starting_values(t_gtk *env)
{
	env->values.width = WIN_WIDTH;
	env->values.height = WIN_HEIGHT;
}

/*
 * to quit the gtk menu window
*/

void		exit(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

/*
 * gtk settings is going to display and manage the general settings of the RT 
 * like the size of the screen or wathever feel free to add things.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gtk scene is going to manage and open what scene we want to display.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gtk object is going to allow us to click and modify objects and lights and why
 * not some other things.
*/

void		ft_gtk_factory(t_gtk *env)
{
	ft_gtk_settings(env);
	ft_gtk_scene(env);
	ft_gtk_object(env);
}
