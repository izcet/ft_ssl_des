/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 16:52:32 by irhett            #+#    #+#             */
/*   Updated: 2017/08/21 21:20:13 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define ASSIGN(A,B,C,D,E,F) init_com(&(c[A].list[B]), C, f_passer(D,E,F))

typedef struct	s_point
{
	void		*parse;
	void		*exec;
	void		*usage;
}				t_point;

/*
** You can't make an array of void pointers, so to pass them requires a struct
*/

static t_point	*f_passer(void *a, void *b, void *c)
{
	t_point		*passer;

	passer = (t_point *)malloc(sizeof(t_point));
	if (!passer)
		return (NULL);
	passer->parse = a;
	passer->exec = b;
	passer->usage = c;
	return (passer);
}

static void		init_com(t_com *c, char *name, t_point *functions)
{
	if (name)
		c->name = ft_strdup(name);
	else
		c->name = ft_strdup("[> Name Space Empty <]");
	if (functions)
	{
		c->parse = functions->parse;
		c->exec = functions->exec;
		c->usage = functions->usage;
		free(functions);
	}
}

static void		populate_lists(t_wrap *c)
{
	ASSIGN(2, 0, "base64", base64_p, base64_e, base64_u);
	ASSIGN(2, 1, "des", NULL, NULL, NULL);
	ASSIGN(2, 2, "des-ecb", NULL, NULL, NULL);
	ASSIGN(2, 3, "dec-cbc", NULL, NULL, NULL);
}


static void		set_wrapper(t_wrap *wrapper, char *name, unsigned int num)
{
	wrapper->name = ft_strdup(name);
	wrapper->num = num;
	wrapper->list = NULL;
	if (num > 0)
	{
		wrapper->list = (t_com *)malloc(sizeof(t_com) * num);
		ft_bzero(wrapper->list, sizeof(t_com) * num);
	}
}

t_wrap			*init_commands(void)
{
	t_wrap	*wrapper;

	wrapper = (t_wrap *)malloc(sizeof(t_wrap) * NUM_COMMAND_TYPES);
	if (!wrapper)
		return (NULL);
	ft_bzero(wrapper, sizeof(t_wrap) * NUM_COMMAND_TYPES);
	set_wrapper(&(wrapper[0]), "Standard", 0);
	set_wrapper(&(wrapper[1]), "Message Digest", 0);
	set_wrapper(&(wrapper[2]), "Cipher", 3);
	populate_lists(wrapper);
	return (wrapper);
}
