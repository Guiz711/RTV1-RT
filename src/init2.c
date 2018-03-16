/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:02:32 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/16 13:03:54 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_fct_arr2(t_args *args)
{
	args->rdr_fct[3] = &render_mode_3;
	args->rdr_fct[4] = &render_mode_4;
	args->spec_fct[PHONG - 1] = &specular_phong;
	args->text_fct[0] = &sine_wave;
	args->text_fct[1] = &sine_cosine_wave;
	args->text_fct[2] = &stripes;
	args->text_fct[3] = &checkerboard;
	args->text_fct[4] = &weight_sum_checkerboard;
	args->text_fct[5] = &map_noise;
	args->text_fct[6] = &fractal_sum_perlin;
	args->text_fct[7] = &sinus_sum_perlin;
	args->bump_fct[0] = &sine_wave_bump;
}

void	init_fct_arr(t_args *args)
{
	args->obj_fct[0] = &sphere_intersection;
	args->obj_fct[1] = &plane_intersection;
	args->obj_fct[2] = &cylinder_intersection;
	args->obj_fct[3] = &cone_intersection;
	args->obj_fct[4] = &paraboloid_intersection;
	args->norm_fct[0] = &sphere_normal;
	args->norm_fct[1] = &plane_normal;
	args->norm_fct[2] = &cylinder_normal;
	args->norm_fct[3] = &cone_normal;
	args->norm_fct[4] = &paraboloid_normal;
	args->rdr_fct[0] = &render_mode_0;
	args->rdr_fct[1] = &render_mode_1;
	args->rdr_fct[2] = &render_mode_2;
	init_fct_arr2(args);
}
