/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_cbc_e.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 00:36:34 by irhett            #+#    #+#             */
/*   Updated: 2017/09/26 00:47:06 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	triple_des_cbc_message(t_des *data)
{
	if (data->decode)
		data->key += 48;
	des_cbc_message(data);
	if (data->decode)
		data->key -= 24;
	else
		data->key += 24;
	data->decode = !data->decode;
	des_cbc_message(data);
	data->decode = !data->decode;
	if (data->decode)
		data->key -= 24;
	else
		data->key += 24;
	des_cbc_message(data);
	if (!data->decode)
		data->key -= 48;
}

int		des3_cbc_e(t_com *com, void *d_t_des)
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
	triple_des_cbc_message(d);
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
