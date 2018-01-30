/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:20:46 by gmichaud          #+#    #+#             */
/*   Updated: 2018/01/30 11:58:57 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

/*
** ft_mtx_mult(t_mtx4 mtx1, t_mtx4 mtx2) : Multiplies two matrices together.
** mtx1 * mtx2 is the order of the operation.
** returns a t_mtx4 matrix containing the matricial product mtx1 * mtx2.
*/

static t_mtx4 mtx_mult_a_b(t_mtx4 m1, t_mtx4 m2)
{
	t_mtx4 m;

	m.a[0] = m1.a[0] * m2.a[0] + m1.a[1] * m2.b[0] + m1.a[2] * m2.c[0]
		+ m1.a[3] * m2.d[0];
	m.a[1] = m1.a[0] * m2.a[1] + m1.a[1] * m2.b[1] + m1.a[2] * m2.c[1]
		+ m1.a[3] * m2.d[1];
	m.a[2] = m1.a[0] * m2.a[2] + m1.a[1] * m2.b[2] + m1.a[2] * m2.c[2]
		+ m1.a[3] * m2.d[2];
	m.a[3] = m1.a[0] * m2.a[3] + m1.a[1] * m2.b[3] + m1.a[2] * m2.c[3]
		+ m1.a[3] * m2.d[3];
	m.b[0] = m1.b[0] * m2.a[0] + m1.b[1] * m2.b[0] + m1.b[2] * m2.c[0]
		+ m1.b[3] * m2.d[0];
	m.b[1] = m1.b[0] * m2.a[1] + m1.b[1] * m2.b[1] + m1.b[2] * m2.c[1]
		+ m1.b[3] * m2.d[1];
	m.b[2] = m1.b[0] * m2.a[2] + m1.b[1] * m2.b[2] + m1.b[2] * m2.c[2]
		+ m1.b[3] * m2.d[2];
	m.b[3] = m1.b[0] * m2.a[3] + m1.b[1] * m2.b[3] + m1.b[2] * m2.c[3]
		+ m1.b[3] * m2.d[3];
	return (m);
}

t_mtx4		mtx4_mult(t_mtx4 m1, t_mtx4 m2)
{
	t_mtx4	m;

	m = mtx_mult_a_b(m1, m2);
	m.c[0] = m1.c[0] * m2.a[0] + m1.c[1] * m2.b[0] + m1.c[2] * m2.c[0]
		+ m1.c[3] * m2.d[0];
	m.c[1] = m1.c[0] * m2.a[1] + m1.c[1] * m2.b[1] + m1.c[2] * m2.c[1]
		+ m1.c[3] * m2.d[1];
	m.c[2] = m1.c[0] * m2.a[2] + m1.c[1] * m2.b[2] + m1.c[2] * m2.c[2]
		+ m1.c[3] * m2.d[2];
	m.c[3] = m1.c[0] * m2.a[3] + m1.c[1] * m2.b[3] + m1.c[2] * m2.c[3]
		+ m1.c[3] * m2.d[3];
	m.d[0] = m1.d[0] * m2.a[0] + m1.d[1] * m2.b[0] + m1.d[2] * m2.c[0]
		+ m1.d[3] * m2.d[0];
	m.d[1] = m1.d[0] * m2.a[1] + m1.d[1] * m2.b[1] + m1.d[2] * m2.c[1]
		+ m1.d[3] * m2.d[1];
	m.d[2] = m1.d[0] * m2.a[2] + m1.d[1] * m2.b[2] + m1.d[2] * m2.c[2]
		+ m1.d[3] * m2.d[2];
	m.d[3] = m1.d[0] * m2.a[3] + m1.d[1] * m2.b[3] + m1.d[2] * m2.c[3]
		+ m1.d[3] * m2.d[3];
	return (m);
}
