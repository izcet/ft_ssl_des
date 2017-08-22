/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 18:40:51 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 19:14:54 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	call_command(t_com command, int argc, char **argv)
{
	void	*data;

	if (command.parse && command.exec && command.usage)
	{
		data = ((void *(*)(int, char **))(command.parse))(argc, argv);
		if (data)
		{
			((void (*)(t_com, void *))(command.exec))(command, data);
		}
		else
			((void (*)(t_com))(command.usage))(command);
	}
	else
		ft_error("Incomplete function pointers associated with this command!");
}
