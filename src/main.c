/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:25:45 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 19:08:20 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		main(int argc, char **argv)
{
	t_wrap		*commands;

	commands = NULL;
	if (argc < 2)
		return (ft_usage(argv[0], "command [command opts] [command args]"));
	commands = init_commands();
	if (!commands)
		return (ft_error("Insufficient memory to allocate command struct."));
	interpret(argv[1], argc, argv, commands);
	delete_commands(commands);
	return (0);
}
