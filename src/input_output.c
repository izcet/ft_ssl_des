/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 13:15:18 by irhett           ###   ########.fr       */
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

unsigned char	*read_data(char *file, char *name, unsigned int *len)
{
	int		fd;
	int		ret;
	char	line[RBUFSIZE + 1];
	char	*data;

	fd = 0;
	if (file && !ft_equals(file, "-"))
		fd = open(file, O_RDONLY);
	if (fd < 0)
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
	//printf("%u\n", *len);
	return ((unsigned char *)data);
}

int			write_to_file(char *str, char *file, char *name, unsigned int len)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (com_err_3(name, "unable to open file '", file, "'"));
	if ((write(fd, str, len)) == -1)
		return (com_err_3(name, "unable to write to file '", file, "'"));
	return (0);
}

