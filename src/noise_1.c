/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42,fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 09:10:18 by gmichaud          #+#    #+#             */
/*   Updated: 2018/03/18 14:43:56 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

static void		shuffle_permutation_table(int *table)
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

static t_vec4	generate_vec4(void)
{
	double	theta;
	double	phi;

	theta = acos(2 * drand48() - 1);
	phi = 2 * drand48() * M_PI;
	return (init_vec4(cos(phi) * sin(theta), sin(phi) * sin(theta),
		cos(theta), 0));
}

void			fill_text_map(t_mat *mat)
{
	size_t	i;

	srand48(mat->noise_seed);
	i = 0;
	while (i < 256)
	{
		mat->noise_map[i] = generate_vec4();
		mat->permutation[i] = i;
		++i;
	}
	shuffle_permutation_table(mat->permutation);
}
