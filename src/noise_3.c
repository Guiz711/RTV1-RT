/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 18:20:46 by jgourdin          #+#    #+#             */
/*   Updated: 2018/03/18 18:20:49 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	permutation(int *perm, int x, int y, int z)
{
	return (perm[perm[perm[x] + y] + z]);
}

void		compute_corners(t_vec4 *map, int *perm, t_noise *p)
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

void		compute_directions(t_noise *p)
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
