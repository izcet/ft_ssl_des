/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/11 22:05:08 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

char	*read_data(char *file, char *invoker, unsigned int *len)
{
	int		fd;
	int		ret;
	char	line[65];
	char	*data;

	fd = 0;
	if (file && !ft_equals(file, "-"))
		fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		com_err_3(invoker, "can't open file: '", file, "'");
		return (NULL);
	}
	ft_bzero(line, sizeof(char) * 65);
	data = ft_strnew(0);
	while ((ret = read(fd, line, 64)) > 0)
	{
		*len += ret;
		data = gnl_concat(data, line, 1, 0);
		ft_bzero(line, sizeof(char) * 65);
	}
	if (ret < 0)
	{
		com_err_3(invoker, "can't read file: '", file, "'");
		free(data);
		return (NULL);
	}
	return (data);
}

int		write_to_file(char *string, char *file, char *invoker)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT);
	if (fd < 0)
		return (com_err_3(invoker, "unable to open file '", file, "'"));
	if ((write(fd, string, ft_strlen(string))) == -1)
		return (com_err_3(invoker, "unable to write to file '", file, "'"));
	return (0);
}

