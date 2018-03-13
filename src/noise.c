/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 09:10:18 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/12 13:49:32 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	lerp(double start, double end, double t)
{
	return (start * (1 - t) + end * t);
}

void	swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	shuffle_permutation_table(int *table)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 256)
	{
		j = lrand48() & 255;
		swap(&table[i], &table[j]);
		table[i + 256] = table[i];
		++i;
	}
}

t_vec4	generate_vec4()
{
	double	theta;
	double	phi;

	theta = acos(2 * drand48() - 1); 
	phi = 2 * drand48() * M_PI; 
 
	return (init_vec4(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta), 0)); 
}

void	fill_text_map(t_mat *mat)
{
	size_t	i;

	// srand48(mat->noise_seed);
	srand48(2011);
	i = 0;
	while (i < 256)
	{
		mat->noise_map[i] = generate_vec4();
		mat->permutation[i] = i;
		++i;
	}
	shuffle_permutation_table(mat->permutation);
}

float	smooth(const float t) 
{
	return t * t * (3 - 2 * t);
} 

int		permutation(int *perm, int x, int y, int z)
{
	return (perm[perm[perm[x] + y] + z]);
}

void	compute_corners(t_vec4 *map, int *perm, t_noise *p)
{
	p->grad[0] = map[permutation(perm, p->start[0], p->start[1], p->start[2])];
	p->grad[1] = map[permutation(perm, p->end[0], p->start[1], p->start[2])];
	p->grad[2] = map[permutation(perm, p->start[0], p->end[1], p->start[2])];
	p->grad[3] = map[permutation(perm, p->end[0], p->end[1], p->start[2])];
	p->grad[4] = map[permutation(perm, p->start[0], p->start[1], p->end[2])];
	p->grad[5] = map[permutation(perm, p->end[0], p->start[1], p->end[2])];
	p->grad[6] = map[permutation(perm, p->start[0], p->end[1], p->end[2])];
	p->grad[7] = map[permutation(perm, p->end[0], p->end[1], p->end[2])];
}

void	compute_directions(t_noise *p)
{
	p->dir[0] = init_vec4(p->t.x, p->t.y, p->t.z, 0);
	p->dir[1] = init_vec4(p->t.x - 1, p->t.y, p->t.z, 0);
	p->dir[2] = init_vec4(p->t.x, p->t.y - 1, p->t.z, 0);
	p->dir[3] = init_vec4(p->t.x - 1, p->t.y - 1, p->t.z, 0);
	p->dir[4] = init_vec4(p->t.x, p->t.y, p->t.z - 1, 0);
	p->dir[5] = init_vec4(p->t.x - 1, p->t.y, p->t.z - 1, 0);
	p->dir[6] = init_vec4(p->t.x, p->t.y - 1, p->t.z - 1, 0);
	p->dir[7] = init_vec4(p->t.x - 1, p->t.y - 1, p->t.z - 1, 0);
}

void	interpolate(t_noise *p)
{
	p->interpol.x = lerp(dot_vec4(p->grad[0], p->dir[0]),
		dot_vec4(p->grad[1], p->dir[1]), p->t.x);
	p->interpol.y = lerp(dot_vec4(p->grad[2], p->dir[2]),
		dot_vec4(p->grad[3], p->dir[3]), p->t.x);
	p->interpol.z = lerp(dot_vec4(p->grad[4], p->dir[4]),
		dot_vec4(p->grad[5], p->dir[5]), p->t.x);
	p->interpol.w = lerp(dot_vec4(p->grad[6], p->dir[6]),
		dot_vec4(p->grad[7], p->dir[7]), p->t.x);
}

double	eval_coord(t_mat *mat, t_vec4 coords)
{
	t_noise	p;

	p.start[0] = floor(coords.x);
	p.start[1] = floor(coords.y);
	p.start[2] = floor(coords.z);
	p.t.x = coords.x - p.start[0];
	p.t.y = coords.y - p.start[1];
	p.t.z = coords.z - p.start[2];
	p.start[0] = p.start[0] & 255;
	p.start[1] = p.start[1] & 255;
	p.start[2] = p.start[2] & 255;
	p.end[0] = p.start[0] + 1 & 255;
	p.end[1] = p.start[1] + 1 & 255;
	p.end[2] = p.start[2] + 1 & 255;
	compute_corners(mat->noise_map, mat->permutation, &p);
	compute_directions(&p);
	p.t.x  = smooth(p.t.x);
	p.t.y  = smooth(p.t.y);
	p.t.z  = smooth(p.t.z);
	interpolate(&p);
	return (lerp(lerp(p.interpol.x, p.interpol.y, p.t.y),
		lerp(p.interpol.z, p.interpol.w, p.t.y), p.t.z));
}

double	map_noise(t_mat *mat, t_vec4 obj_coords)
{
	t_mtx4	rotation;

	rotation = quat_to_mtx(axisangle_to_quat(init_vec4(0, 0, 1, 0), RAD(mat->text_angle)));
	// obj_coords = new_coord(obj_coords, rotation);
	return ((eval_coord(mat, obj_coords) + 1) * 0.5);
}