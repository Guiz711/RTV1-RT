/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:02:24 by gmichaud          #+#    #+#             */
/*   Updated: 2017/12/11 11:03:41 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	check_intersections(t_ray *ray, t_obj_lst *objs, t_inter_fct *obj_fct)
{
	double	inter;

	while (objs)
	{
		inter = obj_fct[objs->content_type](*ray, (void*)objs->content);
		if (inter < ray->inter_dist && inter != -1)
		{
			ray->inter_dist = inter;
			ray->inter_obj = objs;
		}
		objs = objs->next;
	}
}

int		raytracing(t_args *args)
{
	size_t		i;
	t_ray		*rays;

	rays = args->ray_buf;
	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		check_intersections(&(args->ray_buf[i]), args->scene->objs,
			args->obj_fct);
		rays[i].inter = ft_init_vec4(
			rays[i].orig.x + rays[i].dir.x * rays[i].inter_dist,
			rays[i].orig.y + rays[i].dir.y * rays[i].inter_dist,
			rays[i].orig.z + rays[i].dir.z * rays[i].inter_dist, 1);
		if (rays[i].inter_obj && rays[i].inter_obj->content_type == SPHERE)
		{
			rays[i].obj_normal = sphere_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_sphere*)rays[i].inter_obj->content)->color;
		}
		else if (rays[i].inter_obj && rays[i].inter_obj->content_type == PLANE)
		{
			rays[i].obj_normal = plane_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_plane*)rays[i].inter_obj->content)->color;
		}
		else if (rays[i].inter_obj && rays[i].inter_obj->content_type == CYLINDER)
		{
			rays[i].obj_normal = cylinder_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_cylinder*)rays[i].inter_obj->content)->color;
		}
		else if (rays[i].inter_obj && rays[i].inter_obj->content_type == CONE)
		{
			rays[i].obj_normal = cone_normal(rays[i],
				rays[i].inter_obj->content);
			rays[i].color = ((t_cone*)rays[i].inter_obj->content)->color;
		}
		++i;
	}
	return (0);
}
