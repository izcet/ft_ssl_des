/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/11/20 21:55:16 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define RBUFSIZE 64

static char		*append_data(char *str, char *buff, unsigned int l,
		unsigned int r)
{
	char			*final;
	unsigned int	i;

	final = ft_strnew(l + r);
	i = 0;
	while (i < l)
	{
		final[i] = str[i];
		i++;
	}
	i = 0;
	while (i < r)
	{
		final[i + l] = buff[i];
		i++;
	}
	free(str);
	return (final);
}

static int		get_file_descriptor(char *file)
{
	int		fd;

	fd = 0;
	if (file && !ft_equals(file, "-"))
		fd = open(file, O_RDONLY);
	return (fd);
}

unsigned char	*read_data(char *file, char *name, unsigned int *len)
{
	int		fd;
	int		ret;
	char	line[RBUFSIZE + 1];
	char	*data;

	if ((fd = get_file_descriptor(file)) < 0)
	{
		com_err_3(name, "can't open file: '", file, "'");
		return (NULL);
	}
	ft_bzero(line, sizeof(char) * RBUFSIZE + 1);
	data = ft_strnew(0);
	while ((ret = read(fd, line, RBUFSIZE)) > 0)
	{
		data = append_data(data, line, *len, ret);
		*len += ret;
		ft_bzero(line, sizeof(char) * RBUFSIZE + 1);
	}
	if (ret < 0)
	{
		com_err_3(name, "can't read file: '", file, "'");
		free(data);
		return (NULL);
	}
	return ((unsigned char *)data);
}

int				write_to_file(t_output *o)
{
	int		fd;

	if (!o)
		return (0);
	fd = open(o->file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (com_err_3(o->com, "unable to open file '", o->file, "'"));
	if ((write(fd, o->str, o->strlen)) == -1)
		return (com_err_3(o->com, "unable to write to file '", o->file, "'"));
	if (o->newline && (write(fd, "\n", 1) == -1))
		return (com_err_3(o->com, "failed writing newline in '", o->file, "'"));
	free(o);
	return (0);
}

int				write_to_stdout(char *str, int strlen, char b64, char dec)
{
	int		ret;

	ret = write(1, str, strlen);
	if (b64 && !dec)
		ret += write(1, "\n", 1);
	return (ret);
}
