/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 02:33:38 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

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
