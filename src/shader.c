/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 09:46:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/28 13:53:03 by gmichaud         ###   ########.fr       */
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

void	fill_img_buffer(t_env *env, t_pixel *pix)
{
	size_t		i;
	size_t		size;
	uint32_t	hex_col;
	unsigned	char *comp;

	size = env->win_width * env->win_height;
	i = 0;
	while (i < size)
	{
		hex_col = 0;
		comp = (unsigned char*)&hex_col;
		comp[0] = fmax(fmin((int)(pix[i].col_ratio.z * 255), 255), 0);
		comp[1] = fmax(fmin((int)(pix[i].col_ratio.y * 255), 255), 0);
		comp[2] = fmax(fmin((int)(pix[i].col_ratio.x * 255), 255), 0);
		put_pixel(i, env->img, hex_col);
		++i;
	}
}

void	raw_color(t_pixel *pix, t_scene *scn, size_t size)
{
	size_t	i;

	scn = NULL;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj)
			pix[i].col_ratio = dmult_vec3(pix[i].inter.obj->material.amb, 1);
		++i;
	}
}

void	facing_ratio(t_pixel *pix, t_scene *scn, size_t size)
{
	size_t	i;
	double	dot;

	scn = NULL;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj)
		{
			dot = fmax(0, -dot_vec4(pix[i].normal, pix[i].p_ray.dir));
			pix[i].col_ratio = dmult_vec3(pix[i].inter.obj->material.amb, dot);
		}
		++i;
	}
}

void	lambert_model(t_pixel *pix, t_scene *scn, size_t size)
{
	size_t	i;
	double	dot;

	scn = NULL;
	i = 0;
	while (i < size)
	{
		if (pix[i].inter.obj)
		{
			dot = fmax(0, -dot_vec4(pix[i].normal, pix[i].p_ray.dir));
			pix[i].col_ratio = dmult_vec3(pix[i].inter.obj->material.amb, dot);
		}
		++i;
	}
}

int		manage_shaders(t_args *args)
{
	t_scene	*scn;
	size_t	size;
	size_t	i;

	scn = args->scene;
	size = args->env->win_width * args->env->win_height;
	if (scn->shd[NO_SHD])
		args->shd_fct[NO_SHD](args->pix_buf, args->scene, size);
	else if (scn->shd[FACING])
		args->shd_fct[FACING](args->pix_buf, args->scene, size);
	else
	{
		i = 3;
		while(i < COUNT_SHD)
		{
			args->shd_fct[i](args->pix_buf, args->scene, size);
			++i;
		}
	}
	fill_img_buffer(args->env, args->pix_buf);
	return (0);
}
