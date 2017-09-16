/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:55:31 by irhett            #+#    #+#             */
/*   Updated: 2017/09/15 18:01:41 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define ERR_MSG(foo) com_err_3(d->c->name, foo, a[i], "'")

static int	is_flag(int i, int argc, char **argv, char **ptr)
{
	if (i >= argc - 1)
		return (2);
	if (*ptr)
		free(*ptr);
	*ptr = ft_strdup(argv[i + 1]);
	return (0);
}

static int	extended_flags(int i, int argc, char **argv, t_des *d)
{
	if (ft_equals(argv[i], "-i"))
		return (is_flag(i, argc, argv, &(d->infile)));
	if (ft_equals(argv[i], "-o"))
		return (is_flag(i, argc, argv, &(d->outfile)));
	if (ft_equals(argv[i], "-k"))
		return (is_flag(i, argc, argv, (char **)&(d->key)));
	if (d->v && ft_equals(argv[i], "-v"))
		return (is_flag(i, argc, argv, (char **)&(d->iv)));
	return (1);
}

int			des_parse(int argc, char **a, t_des *d)
{
	int		i;
	int		ret;

	i = 1;
	while (++i < argc)
	{
		if (ft_equals(a[i], "-e"))
			d->decode = 0;
		else if (ft_equals(a[i], "-d"))
			d->decode = 1;
		else if (ft_equals(a[i], "-a"))
			d->base64 = 1;
		else
		{
			ret = extended_flags(i, argc, a, d);
			if (ret == 1)
				return (ERR_MSG("invalid option: '"));
			if (ret == 2)
				return (ERR_MSG("option requires argument: '"));
			i++;
		}
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
		if (data->str)
			free(data->str);
		free(data);
	}
	return (NULL);
}

t_des		*create_t_des(t_com *command, int keylen, int v)
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
	data->keylen = keylen;
	data->v = v;
	data->iv = NULL;
	data->c = command;
	data->str = NULL;
	data->strlen = 0;
	return (data);
}
