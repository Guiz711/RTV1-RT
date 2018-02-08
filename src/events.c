/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:56:59 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/08 11:08:13 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		keypress(int keycode, void *args)
{
	if (keycode == KEY_ESC)
		quit((t_args*)args);
	return (SUCCESS);
}