/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 23:37:55 by irhett            #+#    #+#             */
/*   Updated: 2017/09/26 00:55:32 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void			destroy_des3_keys(unsigned char **keys)
{
	int		i;

	if (keys)
	{
		i = -1;
		while (++i < 3)
			if (keys[i])
				free(keys[i]);
		free(keys);
	}
}

unsigned char	**init_des3_keys(unsigned char *key)
{
	unsigned char	**keys;

	keys = (unsigned char **)malloc(sizeof(unsigned char *) * 3);
	if (!keys)
		return (NULL);
	keys[0] = des_key_reduction(key, -1);
	keys[1] = des_key_reduction(key + 8, -1);
	keys[2] = des_key_reduction(key + 16, -1);
	return (keys);
}

void	triple_des_message(t_des *data)
{
	unsigned char	**keys;
	unsigned char	*block;
	unsigned char	*done;
	unsigned int	i;

	keys = init_des3_keys(data->key);
	if (keys)
	{
		i = 0;
		done = (unsigned char *)ft_strnew(0);
		while (i < data->strlen)
		{
			block = (unsigned char *)ft_strnew(8);
			if (data->strlen - i >= 8)
				raw_copy(block, &(data->str[i]), 8);
			else
				raw_copy(block, &(data->str[i]), data->strlen - i);
			i += 8;
			if (!data->decode)
				block = des_ecb_block(block, keys[0], data->decode);
			else
				block = des_ecb_block(block, keys[2], data->decode);
			block = des_ecb_block(block, keys[1], !data->decode);
			if (!data->decode)
				block = des_ecb_block(block, keys[2], data->decode);
			else
				block = des_ecb_block(block, keys[0], data->decode);
			done = raw_append(done, block, i - 8, 8);
		}
		destroy_des3_keys(keys);
		data->strlen = i;
		free(data->str);
		data->str = done;
	}
}

int		des3_e(t_com *com, void *d_t_des)
{
	t_des			*d;
	unsigned char	*temp;
	int				ret;

	ret = 0;
	d = (t_des *)d_t_des;
	d->str = read_data(d->infile, com->name, &(d->strlen));
	if (!d->str)
		return (1);
	if (d->decode && d->base64)
	{
		temp = base64_decode(d->str, BASE64_KEY, &(d->strlen), com->name);
		free(d->str);
		d->str = temp;
	}
	triple_des_message(d);
	if (d->base64 && !d->decode)
	{
		temp = base64_encode(d->str, BASE64_KEY, d->strlen);
		free(d->str);
		d->str = temp;
		d->strlen = ft_strlen((char *)d->str);
	}
	if (d->outfile)
		ret = write_to_file((char *)d->str, d->outfile, com->name, d->strlen);
	else
		write (1, d->str, d->strlen);
	destroy_t_des(d);
	return (ret);
}