/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:32:14 by gmichaud          #+#    #+#             */
/*   Updated: 2017/11/17 09:35:46 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_err	file_len(char *file_name, size_t *file_size)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (ERR_OPEN);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		*file_size += ft_strlen(buffer);
	}
	if (ret == -1)
		return (ERR_READ);
	if (*file_size == 0)
		return (ERR_FILE_EMPTY);
	close(fd);
	return (NO_ERR);
}

static t_err	get_data(char *file_name, char **data)
{
	int		fd;
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (ERR_OPEN);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		ft_strcat(*data, buffer);
	}
	if (ret == -1)
		return (ERR_READ);
	close(fd);
	return (NO_ERR);
}

t_err	read_file(char *file_name, char **data)
{
	t_err	err;
	size_t	file_size;

	err = NO_ERR;
	file_size = 0;
	if ((err = file_len(file_name, &file_size)))
		return (err);
	if (!(*data = ft_strnew(sizeof(**data) * file_size)))
		return (ERR_MALLOC);
	if ((err = get_data(file_name, data)))
		return (err);
	return (NO_ERR);
}
