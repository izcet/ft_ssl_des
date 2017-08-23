/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 18:40:51 by irhett            #+#    #+#             */
/*   Updated: 2017/08/22 17:10:53 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		call_command(t_com *command, int argc, char **argv)
{
	void	*data;
	int		ret;

	ret = 0;
	if (command->parse && command->exec && command->usage)
	{
		data = ((void *(*)(int, char **))(command->parse))(argc, argv);
		if (data)
		{
			//printf("%p\n", data);
			ret = ((int (*)(t_com *, void *))(command->exec))(command, data);
		}
		else
			((void (*)(t_com *))(command->usage))(command);
	}
	else
		ft_error("Incomplete function pointers associated with this command!");
	return (ret);
}
