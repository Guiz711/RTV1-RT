/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:57:38 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/13 13:08:02 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		error(int type, char *text, t_error *err)
{
	if (!text)
		err->detail = NULL;
	else
		err->detail = text;
	err->type = type;
	return (FAILURE);
}