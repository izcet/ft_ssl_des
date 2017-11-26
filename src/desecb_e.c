/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/11/26 15:14:54 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

/*
** back handles the padding for the last block if less than 8 chars
** the else block should be obsoleted by the prepadding done at the beginning
*/

unsigned char	*set_block(unsigned char *str, unsigned int i, unsigned int len)
{
	unsigned char	*block;
	unsigned int	back;

	block = (unsigned char *)ft_strnew(8);
	if (len - i >= 8)
	{
		raw_copy(block, str, 8);
	}
	else
	{
		raw_copy(block, str, len - i);
		back = 7;
		while (back >= (len - i))
			block[back--] = 8 - (len - i);
	}
	return (block);
}

unsigned char	*des_ecb_block(unsigned char *block, unsigned char *key, int d)
{
	unsigned int	i;
	unsigned char	*subkey;
	unsigned char	*left;
	unsigned char	*right;

	des_init_perm(block);
	left = raw_clone(block, 4);
	right = raw_clone(&(block[4]), 4);
	i = 0;
	while (i < 16)
	{
		if (d)
			des_key_r_rot(key, g_des_key_dec[i]);
		else
			des_key_l_rot(key, g_des_key_enc[i]);
		subkey = des_get_subkey(key);
		des_round(left, right, subkey);
		free(subkey);
		swap_ptr((void**)&left, (void**)&right);
		i++;
	}
	free(block);
	block = raw_append(right, left, 4, 4);
	des_final_perm(block);
	return (block);
}

void			des_ecb_message(t_des *data)
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
		block = des_ecb_block(block, subkey, data->decode);
		done = raw_append(done, block, i - 8, 8);
		free(subkey);
	}
	des_pad(data, i, done);
}

int				desecb_e(t_com *c, void *d_t_des)
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
				return (des_act(d, c, des_ecb_message));
			com_err(c->name, "Message not multiple of block length.");
		}
	}
	destroy_t_des(d);
	return (1);
}
