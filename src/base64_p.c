/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:28:08 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 01:38:10 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define PARSE_RESET(foo, bar) if (foo) free (foo); foo = bar

static int	read_data(t_b64 *data)
{
	int		fd;
	int		first;
	int		ret;
	char	*line;

	fd = 0;
	if (data->infile && !ft_equals(data->infile, "-"))
		fd = open(data->infile, O_RDONLY);
	if (fd < 0)
		return (com_err_3("base64", "can't open file: '", data->infile, "'"));
	first = 1;
	while ((ret = get_next_line(fd, &line)) != 0)
	{
		if (!first)
			data->string = gnl_concat(data->string, "\n", 1, 0);
		first = 0;
		data->string = gnl_concat(data->string, line, 1, 1);
	}
	if (ret < 0)
		return (com_err_3("base64", "can't read file: '", data->infile, "'"));
	printf("\"%s\"\n", data->string);
	return (0);
}

static int	parse_done(int argc, char **argv, int i, t_b64 *data)
{
	if (ft_equals(argv[i], "--"))
	{
		if (i + 1 < argc)
		{
			PARSE_RESET(data->infile, ft_strdup(argv[i + 1]));
		}
	}
	else if (ft_equals(argv[i], "-"))
	{
		PARSE_RESET(data->infile, ft_strdup("-"));
	}
	else if (argv[i][0] != '-')
	{
		PARSE_RESET(data->infile, ft_strdup(argv[i]));
	}
	else
		return (com_err_2("base64", "invalid option: ", argv[i]));
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
		else if (ft_equals(argv[i], "-i") || ft_equals(argv[i], "-o"))
		{
			if (i + 1 >= argc)
				return (com_err_2("base64", "option requires an argument: ", 
							argv[i]));
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

void		*base64_p(int argc, char **argv)
{
	t_b64	*data;

	data = (t_b64*)malloc(sizeof(t_b64));
	if (!data)
		return (NULL);
	data->decode = 0;
	data->infile = NULL;
	data->outfile = NULL;
	data->string = ft_strnew(0);
	if (parse_flags(argc, argv, data))
		return (destroy_t_b64(data));
	if (read_data(data))
		return (destroy_t_b64(data));
	return ((void *)data);
}
