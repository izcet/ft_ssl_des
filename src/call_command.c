/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 18:40:51 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 02:51:07 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int		call_command(t_com *c, int argc, char **argv)
{
	void	*data;
	int		ret;

	ret = 0;
	if (c->parse && c->exec && c->usage)
	{
		data = ((void *(*)(t_com *, int, char **))(c->parse))(c, argc, argv);
		if (data)
		{
			ret = ((int (*)(t_com *, void *))(c->exec))(c, data);
		}
		else
			((void (*)(t_com *))(c->usage))(c);
	}
	else
		ft_error("Incomplete function pointers associated with this command!");
	return (ret);
}
