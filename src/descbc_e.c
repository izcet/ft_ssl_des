/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descbc_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/09/19 21:54:31 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void			des_cbc_message_decrypt(t_des *data)
{
	unsigned char	*done;
	unsigned char	*block;
	unsigned char	*subkey;
	unsigned int	i;

	done = (unsigned char *)ft_strnew(data->strlen);
	i = data->strlen - 8;
	while (i < data->strlen)
	{
		subkey = des_key_reduction(data->key, -1);
		block = (unsigned char *)ft_strnew(8);
		raw_copy(block, &(data->str[i]), 8);
		i -= 8;
		block = des_ecb_block(block, subkey, data->decode);
	//	if (i > data->strlen)
			raw_xor(block, data->iv, 8);
	//	else
	//		raw_xor(block, &(data->str[i]), 8);
		done = raw_append(block, done, 8, data->strlen - (i + 16));
		free(subkey);
	}
	free(data->str);
	data->str = done;
}

void			des_cbc_message_encrypt(t_des *data)
{
	unsigned char	*done;
	unsigned char	*block;
	unsigned char	*subkey;
	unsigned int	i;

	done = (unsigned char *)ft_strnew(data->strlen);
	i = 0;
	while (i < data->strlen)
	{
		subkey = des_key_reduction(data->key, -1);
		block = (unsigned char *)ft_strnew(8);
		if (data->strlen - i >= 8)
			raw_copy(block, &(data->str[i]), 8);
		else
			raw_copy(block, &(data->str[i]), data->strlen - i);
		i += 8;
		raw_xor(block, data->iv, 8);
		free(data->iv);
		block = des_ecb_block(block, subkey, data->decode);
		data->iv = raw_clone(block, 8);
		done = raw_append(done, block, i - 8, 8);
		free(subkey);
	}
	data->strlen = i;
	free(data->str);
	data->str = done;
}

int				descbc_e(t_com *com, void *d_t_des)
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
	if (d->decode)
		des_cbc_message_decrypt(d);
	else
		des_cbc_message_encrypt(d);
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
		write(1, d->str, d->strlen);
	destroy_t_des(d);
	return (ret);
}
