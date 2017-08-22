/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:34:40 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 19:10:15 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static int	get_index(char *name, t_wrap *commands, int type_index)
{
	unsigned int	index;

	index = 0;
	ft_strtolower(name);
	while (index < commands[type_index].num)
	{
		if (ft_equals(commands[type_index].list[index].name, name))
			return ((int)index);
		index++;
	}
	return (-1);
}

void	interpret(char *name, int argc, char **argv, t_wrap *commands)
{
	int		type_index;
	int		command_index;

	type_index = 0;
	while (type_index < NUM_COMMAND_TYPES && command_index < 0)
		command_index = get_index(name, commands, type_index++);
	if (type_index == NUM_COMMAND_TYPES)
		print_command_list(commands);
	else
	{
		call_command(commands[type_index].list[command_index], argc, argv);
	}
}
