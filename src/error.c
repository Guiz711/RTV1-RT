/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:57:38 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/15 10:43:20 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	error(t_err err)
{
	if (err == ERR_OPEN)
		perror("Open error");
	if (err == ERR_READ)
		perror("Read error");
	ft_putnbr(err);
}