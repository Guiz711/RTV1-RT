/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:15:53 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/28 05:49:19 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(int pos, t_img *img, unsigned int color)
{
	char	*data;
	int		width;
	int		inc;

	data = img->data;
	inc = img->color_depth / 8;
	width = img->width; //* (COLOR_DEPTH / 8);
	ft_memcpy(&data[pos * inc], &color, sizeof(color));
}

void	convert_color(t_env *env, size_t pos, t_vec3 pix_col)
{
	uint32_t	hex_col;
	unsigned	char *comp;

	hex_col = 0;
	comp = (unsigned char*)&hex_col;
	comp[0] = fmax(fmin((int)(pix_col.z * 255), 255), 0);
	comp[1] = fmax(fmin((int)(pix_col.y * 255), 255), 0);
	comp[2] = fmax(fmin((int)(pix_col.x * 255), 255), 0);
	put_pixel(pos, env->img, hex_col);
}

int		double_not_null(double d)
{
	if (d > 1e-6 || d < -1e-6)
		return TRUE;
	return FALSE;
}

void	invert(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}
