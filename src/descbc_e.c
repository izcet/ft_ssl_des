/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descbc_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 17:56:16 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 22:41:10 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

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
		if (!data->decode)
		{
			raw_xor(block, data->iv, 8);
			free(data->iv);
		}
		block = des_ecb_block(block, subkey, data->decode);
		if (data->decode)
		{
			raw_xor(block, data->iv, 8);
			free(data->iv);
			data->iv = raw_clone(&(data->str[i - 8]), 8);
		}
		else
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

	d = (t_des *)d_t_des;
	d->str = read_data(d->infile, com->name, &(d->strlen));
	if (!d->str)
		return (1);
	return (des_act(d, com, des_cbc_message));
}
