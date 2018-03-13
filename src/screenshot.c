/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 02:56:01 by jgourdin          #+#    #+#             */
/*   Updated: 2018/02/28 08:16:59 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*find_new_name(void)
{
	int		i;
	char	*filename;

	i = 0;
	while (fopen(ft_strjoin("./screenshots/",ft_strjoin(ft_itoa(i), ".ppm")), "r"))
		i++;
	filename = ft_strjoin("./screenshots/",ft_strjoin(ft_itoa(i), ".ppm"));
	printf("%s\n", filename);
	return (filename);
}

void		write_header(FILE *fp)
{
	char	*header;
	size_t		size;
	size_t		len;

	header = ft_strjoin("P3\n", ft_itoa(WIN_WIDTH));
	header = ft_strjoin(header, " ");
	header = ft_strjoin(header, ft_itoa (WIN_HEIGHT));
	header = ft_strjoin(header, "\n255\n");
	len = ft_strlen(header);
	size = sizeof(char);
	fwrite(header,size,len,fp);
}



void		screenshot(t_img *img)
{
	char	*name;
	FILE	*fp;
	size_t	i;
	size_t	p;
	size_t		nb;
	char	*nbr;
	char	*tmp;
//	int		caca;


	tmp = ft_strnew(((WIN_WIDTH * WIN_HEIGHT) * 3) + ((WIN_WIDTH * WIN_HEIGHT * 3) * 3) + WIN_HEIGHT + 1);
	i = 0;
	p = 0;
	name = find_new_name();
	fp = fopen(name, "w+");
	write_header(fp);
	img->data[0] = 98;
	while (i < WIN_WIDTH * WIN_HEIGHT * 4)
	{
		nb = 0;
			if ((int)img->data[i + 2] < 0)
				nbr = ft_itoa(((int)(255 + (img->data[i + 2]))));
			else
				nbr = ft_itoa((int)(img->data[i + 2]));
			ft_strcpy(&tmp[p], nbr);
			p += ft_strlen(nbr);
			tmp[p] = ' ';
			p++;
			if ((int)img->data[i + 1] < 0)
				nbr = ft_itoa(((int)(255 + img->data[i + 1])));
			else
				nbr = ft_itoa((int)(img->data[i + 1]));
			ft_strcpy(&tmp[p], nbr);
			p += ft_strlen(nbr);
			tmp[p] = ' ';
			p++;
			if ((int)img->data[i] < 0)
				nbr = ft_itoa(((int)(255 + img->data[i])));
			else
				nbr = ft_itoa((int)(img->data[i]));
			ft_strcpy(&tmp[p], nbr);
			p += ft_strlen(nbr);
			tmp[p] = ' ';
			p++;
			i += 4;
	}
	printf("%d = %d = %d\n", (int)img->data[0], (int)img->data[1], (int)img->data[2]);
//	printf("%s\n", tmp);
	i = 0;
	fwrite(tmp, sizeof(char), ft_strlen(tmp), fp);
}
