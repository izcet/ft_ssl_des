/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/09/15 14:04:27 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

unsigned char	*des_ecb_block(unsigned char *block, unsigned char *key, int d)
{
	unsigned int		i;
	unsigned char	*subkey;
	unsigned char	*left;
	unsigned char	*right;

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
	return (raw_append(left, right, 4, 4));
}

void	des_ecb_message(t_des *data)
{
	unsigned char	*done;
	unsigned char	*block;
	unsigned char	*subkey;
	unsigned int	i;

	done = (unsigned char *)ft_strnew(data->strlen);
	subkey = des_key_reduction(data->key, -1);
	i = 0;
	while (i < data->strlen)
	{
		block = (unsigned char *)ft_strnew(8);
		ft_bzero((char *)block, sizeof(char) * 8);
		if (data->strlen - i >= 8)
			raw_copy(block, &(data->str[i]), 8);
		else
			raw_copy(block, &(data->str[i]), data->strlen - i);
		i += 8;
		block = des_ecb_block(block, subkey, data->decode);
		done = raw_append(done, block, i - 8, 8);
	}
	free(subkey);
	data->strlen = i;
	free(data->str);
	data->str = done;
}

int		desecb_e(t_com *c, void *d_t_des)
{
	t_des			*d;
	unsigned char	*temp;
	int				ret;

	ret = 0;
	d = (t_des *)d_t_des;
	d->c = c;
	d->str = read_data(d->infile, d->c->name, &(d->strlen));
	if (!d->str)
		return (1);
	if (d->decode && d->base64)
	{
		temp = base64_decode(d->str, BASE64_KEY, &(d->strlen), c->name);
		free(d->str);
		d->str = temp;
	}
	des_ecb_message(d);
	if (d->base64 && !d->decode)
	{
		temp = base64_encode(d->str, BASE64_KEY, d->strlen);
		free(d->str);
		d->str = temp;
		d->strlen = ft_strlen((char *)d->str);
	}
	if (d->outfile)
		ret = write_to_file((char *)d->str, d->outfile, c->name, d->strlen);
	else
	{
		write(1, d->str, d->strlen);
		if (!d->decode)
			ft_putchar('\n');
	}
	destroy_t_des(d);
	return (ret);
}
