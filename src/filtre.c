/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:59:17 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/26 12:41:38 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		filter_selector(t_args *args)
{
	if (args->scene->filtre == 1)
		bandw_filter(args->env->img);
	else if (args->scene->filtre == 2)
		negatif_filter(args->env->img);
	else if (args->scene->filtre == 3)
		stereoscopie_filter(args->env->img);
	else if (args->scene->filtre == 4)
		sepia_filter(args->env->img);
	else if (args->scene->filtre == 5)
		motionblur_filter(args->env->img);
	else if (args->scene->filtre == 6)
		cartoon_filter(args->env->img);
}

void		bandw_filter(t_img *img)
{
	size_t				i;
	unsigned int		x;
	unsigned int		max;
	unsigned char		*data;

	data = (unsigned char *)img->data;
	max = ((WIN_HEIGHT * WIN_WIDTH) * 4) - 4;
	i = 0;
	while (i < max)
	{
		x = data[i + 2] + data[i + 1] + data[i];
		x /= 3;
		*((unsigned int *)(data + i)) = x | x << 8 | x << 16 | data[i + 3] << 24;
		i += 4;
	}
}

void		negatif_filter(t_img *img)
{
	size_t			i;
	unsigned int	max;
	unsigned char	*data;

	data = (unsigned char *)img->data;
	max = ((WIN_HEIGHT * WIN_WIDTH) * 4) - 4;
	i = 0;
	while (i < max)
	{
		data[i] = 255 - data[i];
		data[i + 1] = 255 - data[i + 1];
		data[i + 2] = 255 - data[i + 2];
		i+= 4;
	}
}

void		stereoscopie_filter(t_img *img)
{
	size_t		i;
	int			tmp;
	size_t		max;
	unsigned char *data;

	data = (unsigned char *)img->data;
	max = ((WIN_HEIGHT * WIN_WIDTH) * 4);
	i = 0;
	while (i < max)
	{
		tmp = i + 1 - 80 - (WIN_WIDTH * 4) * 20;
		if (tmp > 0)
		{
			data[tmp] = data[i + 1];
			data[i + 1] = 0;
			tmp = i - 80 - (WIN_WIDTH * 4) * 20;
			data[tmp] = data[i];
			data[i] = 0;
		}
		i += 4;
	}
}

void		sepia_filter(t_img *img)
{
	size_t	i;
	size_t	max;
	unsigned char *data;

	data = (unsigned char *)img->data;
	max = ((WIN_HEIGHT * WIN_WIDTH) * 4) - 4;
	i = 0;
	while (i < max)
	{
		data[i + 2] = (0.393 * data[i + 2]) + (0.769 * data[i + 1]) + (0.189 * data[i]) > 255 ? 255 : (0.393 * data[i + 2]) + (0.769 * data[i + 1]) + (0.189 * data[i]);
		data[i + 1] = (0.349 * data[i + 2]) + (0.686 * data[i + 1]) + (0.168 * data[i]) > 255 ? 255 : (0.349 * data[i + 2]) + (0.686 * data[i + 1]) + (0.168 * data[i]);
		data[i] = (0.272 * data[i + 2]) + (0.534 * data[i + 1]) + (0.131 * data[i]) > 255 ? 255 : (0.272 * data[i + 2]) + (0.534 * data[i + 1]) + (0.131 * data[i]);
		i += 4;
	}
}

void		motionblur_filter(t_img *img)
{
	unsigned char	*data;
	int				tmp;
	int				x;
	int				y;
	int				moyenne;
	int				i;
	int				blurate;

	blurate = 5;
	data = (unsigned char *)img->data;
	i = 0;
	while (i < (WIN_HEIGHT * img->width))
	{
		x = 0;
		moyenne = 0;
		while (x < (blurate * 4))
		{
			y = 0;
			while (y < (blurate * 4))
			{
				tmp = i + x + (y * img->width);
				if (tmp > 0 && tmp < WIN_WIDTH * WIN_HEIGHT * 4)
				{
					moyenne += (data[tmp]);
					if (data[tmp] < 0)
					moyenne += 256;
				}
				y += 4;
			}
			x += 4;
		}
		moyenne /= (blurate * blurate);
		data[i] = moyenne;
		i++;
	}
}

int			cartoon_filter(t_img *img)
{
	size_t	i;
	size_t	max;
	unsigned char *data;
	size_t	j;

	data = (unsigned char *)img->data;
	i = 0;
	max = (WIN_HEIGHT * WIN_WIDTH *4);
	while (i < max)
	{
		j = 0;
		if (i > max)
			return (0);
		printf("%zu\n", i);
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
		i += 4;
	}
	return (0);
}
