/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:55:31 by irhett            #+#    #+#             */
/*   Updated: 2017/09/11 22:34:56 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define PARSE_RESET(foo, bar) if (foo) free(foo); foo = ft_strdup(bar)
#define WHOOPS return (com_err_3(d->c->name, "invalid option: '", a[i], "'"))

static int	is_flag(char *argv, char *flag, char *next, char *ptr)
{
	if (ft_equals(argv, flag))
	{
		PARSE_RESET(ptr, next);
		return (1);
	}
	return (0);
}

static int	parse_flags(int argc, char **a, t_des *d)
{
	int		i;

	i = 1;
	while (++i < argc)
	{
		if (ft_equals(a[i], "-e"))
			d->decode = 0;
		else if (ft_equals(a[i], "-d"))
			d->decode = 1;
		else if (ft_equals(a[i], "-a"))
			d->base64 = 1;
		else if (argc > i + 1)
		{
			// update this section to more closely align with the base64 parsing
			// make sure these flags have a value
			// make sure values line up correctly
			if (!is_flag(a[i], "-i", a[i + 1], d->infile))
				if (!is_flag(a[i], "-o", a[i + 1], d->outfile))
					if (!is_flag(a[i], "-k", a[i + 1], d->key))
						if ((d->v) && !is_flag(a[i], "-v", a[i + 1], d->iv))
							WHOOPS;
			i++;
		}
		else
			WHOOPS;
	}
	return (0);
}

void		*destroy_t_des(t_des *data)
{
	if (data)
	{
		if (data->infile)
			free(data->infile);
		if (data->outfile)
			free(data->outfile);
		if (data->key)
			free(data->key);
		if (data->iv)
			free(data->iv);
		free(data);
	}
	return (NULL);
}

void		*desecb_p(t_com *command, int argc, char **argv)
{
	t_des	*data;

	data = (t_des *)malloc(sizeof(t_des));
	if (!data)
		return (NULL);
	data->decode = 0;
	data->base64 = 0;
	data->infile = NULL;
	data->outfile = NULL;
	data->key = NULL;
	data->keylen = 8;
	data->v = 0;
	data->iv = NULL;
	data->c = command;
	if (parse_flags(argc, argv, data))
		return (destroy_t_des(data));
	if (des_validate_key(data))
		return (destroy_t_des(data));
	return (NULL);
}
