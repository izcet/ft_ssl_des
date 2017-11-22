/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descbc_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/11/22 14:13:44 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void			cbc_pre_block(t_des *data, unsigned char *block)
{
	if (!data->decode)
	{
		raw_xor(block, data->iv, 8);
		free(data->iv);
	}
}

void			cbc_post_block(t_des *data, unsigned char *blk, unsigned int i)
{
	if (data->decode)
	{
		raw_xor(blk, data->iv, 8);
		free(data->iv);
		data->iv = raw_clone(&(data->str[i - 8]), 8);
	}
	else
		data->iv = raw_clone(blk, 8);
}

void			des_cbc_message(t_des *data)
{
	unsigned char	*done;
	unsigned char	*block;
	unsigned char	*subkey;
	unsigned int	i;

	done = (unsigned char *)ft_strnew(0);
	i = 0;
	while (i < data->strlen)
	{
		subkey = des_key_reduction(data->key, -1);
		block = set_block(&(data->str[i]), i, data->strlen);
		i += 8;
		cbc_pre_block(data, block);
		block = des_ecb_block(block, subkey, data->decode);
		cbc_post_block(data, block, i);
		done = raw_append(done, block, i - 8, 8);
		free(subkey);
	}
	des_pad(data, i, done);
}

int				descbc_e(t_com *c, void *d_t_des)
{
	t_des			*d;
	unsigned char	*temp;

	d = (t_des *)d_t_des;
	if ((d->str = read_data(d->infile, d->c->name, &(d->strlen))))
	{
		if (d->str && d->decode && d->base64)
		{
			temp = base64_decode(d->str, BASE64_KEY, &(d->strlen), c->name);
			free(d->str);
			d->str = temp;
		}
		if (d->str)
		{
			des_pad_input(d);
			if (!d->decode || ((d->strlen % 8) == 0))
				return (des_act(d, c, des_cbc_message));
			com_err(c->name, "Message not multiple of block length.");
		}
	}
	destroy_t_des(d);
	return (1);
}
