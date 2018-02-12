/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:15:53 by gmichaud          #+#    #+#             */
/*   Updated: 2018/02/12 10:41:12 by gmichaud         ###   ########.fr       */
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

void	process_color(t_env *env, t_pixel *pix, size_t pos, t_vec3 pix_col)
{
	// t_vec3		ratio;
	uint32_t	hex_col;
	unsigned	char *comp;

	pix = NULL;
	// ratio.x = pix->amb_ratio.x + pix->diff_ratio.x + pix->spec_ratio.x;
	// ratio.y = pix->amb_ratio.y + pix->diff_ratio.y + pix->spec_ratio.y;
	// ratio.z = pix->amb_ratio.z + pix->diff_ratio.z + pix->spec_ratio.z;
	hex_col = 0;
	comp = (unsigned char*)&hex_col;
	comp[0] = fmax(fmin((int)(pix_col.z * 255), 255), 0);
	comp[1] = fmax(fmin((int)(pix_col.y * 255), 255), 0);
	comp[2] = fmax(fmin((int)(pix_col.x * 255), 255), 0);
	put_pixel(pos, env->img, hex_col);
}