/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:52:32 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 19:11:47 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		init_com(t_com c, char *name, void *functions[3])
{
	if (name)
		c.name = ft_strdup(name);
	else
		c.name = ft_strdup("[> Name Space Empty <]");
	c.parse = functions[0];
	c.exec = functions[1];
	c.usage = functions[2];
}

static void		set_wrapper(t_wrap wrapper, char *name, unsigned int num)
{
	wrapper.name = ft_strdup(name);
	wrapper.num = num;
	wrapper.list = NULL;
	if (num > 0)
		wrapper.list = (t_com *)malloc(sizeof(t_com) * num);
}

static void		populate_lists(t_wrap *c)
{
	init_com(c[2].list[0], "base64", (void *[3]){NULL, NULL, NULL});
	init_com(c[2].list[1], "des-ecb", (void *[3]){NULL, NULL, NULL});
	init_com(c[2].list[2], "dec-cbc", (void *[3]){NULL, NULL, NULL});
}

t_wrap			*init_commands(void)
{
	t_wrap	*wrapper;

	wrapper = (t_wrap *)malloc(sizeof(t_wrap) * NUM_COMMAND_TYPES);
	if (!wrapper)
		return (NULL);
	set_wrapper(wrapper[0], "Standard", 0);
	set_wrapper(wrapper[1], "Message Digest", 0);
	set_wrapper(wrapper[2], "Cipher", 3);
	populate_lists(wrapper);
	return (wrapper);
}
