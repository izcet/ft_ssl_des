/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:52:32 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 21:41:56 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void		del_com(t_com *com)
{
	if (com->name)
		free(com->name);
}

void		delete_commands(t_wrap *commands)
{
	unsigned int	type_i;
	unsigned int	comm_i;

	type_i = 0;
	while (type_i < NUM_COMMAND_TYPES)
	{
		comm_i = 0;
		while (comm_i < commands[type_i].num)
			del_com(&(commands[type_i].list[comm_i++]));
		if (commands[type_i].list)
			free(commands[type_i].list);
		if (commands[type_i].name)
			free(commands[type_i].name);
		type_i++;
	}
	free(commands);
}

void		print_command_list(t_wrap *commands, char *error)
{
	unsigned int	type_i;
	unsigned int	comm_i;

	if (error)
	{
		ft_putstr_fd("ft_ssl: Error: '", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd("' is an invalid command.", 2);
		ft_putchar('\n');
	}
	type_i = 0;
	while (type_i < NUM_COMMAND_TYPES)
	{
		ft_putstr(commands[type_i].name);
		ft_putendl(" commands:");
		comm_i = 0;
		while (comm_i < commands[type_i].num)
			ft_putendl(commands[type_i].list[comm_i++].name);
		ft_putchar('\n');
		type_i++;
	}
}
