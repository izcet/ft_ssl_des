/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3cbc_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 00:36:34 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 23:16:02 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	triple_des_cbc_message(t_des *data)
{
	unsigned char	**keys;
	unsigned char	*block;
	unsigned char	*done;
	unsigned int	i;

	i = 0;
	done = (unsigned char *)ft_strnew(0);
	while (i < data->strlen)
	{
		keys = init_des3_keys(data->key);
		block = set_block(&(data->str[i]), i, data->strlen);
		i += 8;
		cbc_pre_block(data, block);
		block = des3_block(block, keys, data->decode);
		cbc_post_block(data, block, i);
		done = raw_append(done, block, i - 8, 8);
		destroy_des3_keys(keys);
	}
	data->strlen = i;
	free(data->str);
	data->str = done;
}

int		des3cbc_e(t_com *com, void *d_t_des)
{
	t_des			*d;

	d = (t_des *)d_t_des;
	d->str = read_data(d->infile, com->name, &(d->strlen));
	if (!d->str)
		return (1);
	return (des_act(d, com, triple_des_cbc_message));
}
