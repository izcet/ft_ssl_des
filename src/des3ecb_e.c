/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3ecb_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 23:37:55 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 22:39:13 by irhett           ###   ########.fr       */
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

unsigned char	*des3_block(unsigned char *block, unsigned char **keys, int d)
{
	if (!d)
		block = des_ecb_block(block, keys[0], d);
	else
		block = des_ecb_block(block, keys[2], d);
	block = des_ecb_block(block, keys[1], !d);
	if (!d)
		block = des_ecb_block(block, keys[2], d);
	else
		block = des_ecb_block(block, keys[0], d);
	return (block);
}

void			triple_des_message(t_des *data)
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
		if (data->strlen - i >= 8)
			raw_copy(block, &(data->str[i]), 8);
		else
			raw_copy(block, &(data->str[i]), data->strlen - i);
		i += 8;
		block = des3_block(block, keys, data->decode);
		done = raw_append(done, block, i - 8, 8);
		destroy_des3_keys(keys);
	}
	data->strlen = i;
	free(data->str);
	data->str = done;
}

int				des3ecb_e(t_com *com, void *d_t_des)
{
	t_des			*d;

	d = (t_des *)d_t_des;
	if (!(d->str = read_data(d->infile, com->name, &(d->strlen))))
		return (1);
	return (des_act(d, com, triple_des_message));
}
