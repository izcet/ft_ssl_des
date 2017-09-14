/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:28:08 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 21:56:45 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define PARSE_RESET(foo, bar) if (foo) free(foo); foo = bar
#define FEQ ft_equals

static int	parse_done(int argc, char **argv, int i, t_b64 *d)
{
	if (ft_equals(argv[i], "-i") || ft_equals(argv[i], "-o"))
		return (com_err_2(d->c->name, "option requires argument: ", argv[i]));
	if (ft_equals(argv[i], "--"))
	{
		if (i + 1 < argc)
		{
			PARSE_RESET(d->infile, ft_strdup(argv[i + 1]));
		}
	}
	else if (ft_equals(argv[i], "-"))
	{
		PARSE_RESET(d->infile, ft_strdup("-"));
	}
	else if (argv[i][0] != '-')
	{
		PARSE_RESET(d->infile, ft_strdup(argv[i]));
	}
	else
		return (com_err_2(d->c->name, "invalid option: ", argv[i]));
	return (0);
}

static int	parse_flags(int argc, char **argv, t_b64 *data)
{
	int		i;

	i = 1;
	while (++i < argc)
	{
		if (ft_equals(argv[i], "-e"))
			data->decode = 0;
		else if (ft_equals(argv[i], "-d"))
			data->decode = 1;
		else if ((argc > i + 1) && (FEQ(argv[i], "-i") | FEQ(argv[i], "-o")))
		{
			if (ft_equals(argv[i], "-i"))
			{
				PARSE_RESET(data->infile, ft_strdup(argv[i + 1]));
			}
			else
			{
				PARSE_RESET(data->outfile, ft_strdup(argv[i + 1]));
			}
			i++;
		}
		else
			return (parse_done(argc, argv, i, data));
	}
	return (0);
}

void		*destroy_t_b64(t_b64 *data)
{
	if (data)
	{
		if (data->infile)
			free(data->infile);
		if (data->outfile)
			free(data->outfile);
		if (data->string)
			free(data->string);
		free(data);
	}
	return (NULL);
}

void		*base64_p(t_com *command, int argc, char **argv)
{
	t_b64	*data;

	data = (t_b64*)malloc(sizeof(t_b64));
	if (!data)
		return (NULL);
	data->decode = 0;
	data->infile = NULL;
	data->outfile = NULL;
	data->string = (unsigned char *)ft_strnew(0);
	data->strlen = 0;
	data->c = command;
	if (parse_flags(argc, argv, data))
		return (destroy_t_b64(data));
	data->string = read_data(data->infile, command->name, &(data->strlen));
	if (data->string == NULL)
		return (destroy_t_b64(data));
	return ((void *)data);
}
