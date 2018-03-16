/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:50:42 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/16 17:26:27 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					motion_calc(t_img *img, int moyenne, int i, int x)
{
	int				y;
	int				tmp;

	y = 0;
	while (y < 20)
	{
		tmp = i + x + (y * img->width);
		if (tmp > 0 && tmp < WIN_WIDTH * WIN_HEIGHT * 4)
		{
			moyenne += (img->data[tmp]);
			if (img->data[tmp] < 0)
				moyenne += 256;
		}
		y += 4;
	}
	return (moyenne);
}

void				motionblur_filter(t_img *img)
{
	int				x;
	int				moyenne;
	int				i;

	i = 0;
	while (i < (WIN_HEIGHT * img->width))
	{
		x = 0;
		moyenne = 0;
		while (x < 20)
		{
			moyenne = motion_calc(img, moyenne, i, x);
			x += 4;
		}
		moyenne /= 25;
		img->data[i] = moyenne;
		i++;
	}
}

void				cartoon_calc(unsigned char *data, int i)
{
	int				j;

	j = 0;
	while (j < 3)
	{
		if (data[i + j] < 51)
			data[i + j] = 30;
		else if (data[i + j] < 102)
			data[i + j] = 70;
		else if (data[i + j] < 153)
			data[i + j] = 153;
		else if (data[i + j] < 204)
			data[i + j] = 204;
		else if (data[i + j] < 255)
			data[i + j] = 255;
		j++;
	}
}

int					cartoon_filter(t_img *img)
{
	size_t			i;
	size_t			max;
	unsigned char	*data;

	data = (unsigned char *)img->data;
	i = 0;
	max = (WIN_HEIGHT * WIN_WIDTH * 4);
	while (i < max)
	{
		if (i > max)
			return (0);
		cartoon_calc(data, i);
		i += 4;
	}
	return (0);
}
