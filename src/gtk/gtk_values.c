/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 17:20:01 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/07 18:20:48 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/* it just have to modify the size of the screen BUT later we will have to update every modifications the user made
*/

void			ft_update(GtkButton *btn, t_gtk *env)
{
	gtk_widget_destroy(env->settings.pwindow);
	WIN_WIDTH = env->values.width > 2560 ? 2560 : env->values.width;
	WIN_HEIGHT = env->values.height > 1440 ? 1440 : env->values.height;
	trace_primary_rays(env);
}


