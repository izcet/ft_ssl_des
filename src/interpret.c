/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:34:40 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 01:41:42 by irhett           ###   ########.fr       */
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

int			interpret(char *name, int argc, char **argv, t_wrap *commands)
{
	int		type_index;
	int		index;
	int		ret;

	type_index = 0;
	index = -1;
	ret = 0;
	while (type_index < NUM_COMMAND_TYPES && index < 0)
	{
		index = get_index(name, commands, type_index);
		if (index == -1)
			type_index++;
	}
	if (type_index == NUM_COMMAND_TYPES)
		print_command_list(commands, name);
	else
	{
		ret = call_command(&(commands[type_index].list[index]), argc, argv);
	}
	return (ret);
}
