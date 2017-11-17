/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:57:38 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/17 11:36:39 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		error_message(const char *message, size_t line)
{
	ft_putstr_fd("Error line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
	return (FAILURE);
}

void	error(t_err err)
{
	if (err == ERR_OPEN)
		perror("Open error");
	if (err == ERR_READ)
		perror("Read error");
	ft_putnbr(err);
}