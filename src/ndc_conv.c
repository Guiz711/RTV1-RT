/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ndc_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:38:32 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/19 11:17:47 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** ft_ndc_conv(t_vec4 v): normalizes a vector for Normalized Device Coordinates.
** returns a normalized vector.
**
** ft_arr_ndc_conv(t_vtx *v_arr, size_t size): normalizes an array of vertices
** into Normalized Device Coordinates.
** v_arr is a vertices array and size is the length of the array.
*/

t_vec2	ft_ndc_conv_2(t_vec2 v)
{
	t_vec2 v_norm;
	
	v_norm.x = (v.x + 0.5) / WIN_WIDTH;
	v_norm.y = (v.y + 0.5) / WIN_HEIGHT;
	return (v_norm);
}

void	ft_arr_ndc_conv(t_vtx *v_arr, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		v_arr[i].pos = ft_ndc_conv(v_arr[i].pos);
		i++;
	}
}
