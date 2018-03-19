/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 13:02:32 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/19 13:16:12 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_fct_arr3(t_args *args)
{
	args->modif_scale[0] = &scale_sphere;
	args->modif_scale[2] = &scale_cylinder;
	args->modif_scale[3] = &scale_cone;
	args->modif_scale[4] = &scale_parab;
	args->modif_scale[5] = &scale_triangle;
	args->modif_trans[0] = &trans_sphere;
	args->modif_trans[1] = &trans_plane;
	args->modif_trans[2] = &trans_cylinder;
	args->modif_trans[3] = &trans_cone;
	args->modif_trans[4] = &trans_parab;
	args->modif_trans[5] = &trans_triangle;
	args->modif_rot[1] = &rot_plane;
	args->modif_rot[2] = &rot_cylinder;
	args->modif_rot[3] = &rot_cone;
	args->modif_rot[4] = &rot_parab;
	args->modif_rot[5] = &rot_triangle;
}

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
	init_fct_arr3(args);
}

void	init_fct_arr(t_args *args)
{
	args->obj_fct[0] = &sphere_intersection;
	args->obj_fct[1] = &plane_intersection;
	args->obj_fct[2] = &cylinder_intersection;
	args->obj_fct[3] = &cone_intersection;
	args->obj_fct[4] = &paraboloid_intersection;
	args->obj_fct[5] = &triangle_intersection;
	args->norm_fct[0] = &sphere_normal;
	args->norm_fct[1] = &plane_normal;
	args->norm_fct[2] = &cylinder_normal;
	args->norm_fct[3] = &cone_normal;
	args->norm_fct[4] = &paraboloid_normal;
	args->norm_fct[5] = &triangle_normal;
	args->rdr_fct[0] = &render_mode_0;
	args->rdr_fct[1] = &render_mode_1;
	args->rdr_fct[2] = &render_mode_2;
	init_fct_arr2(args);
}
