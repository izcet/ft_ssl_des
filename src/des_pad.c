/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_pad.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:24:37 by irhett            #+#    #+#             */
/*   Updated: 2017/11/26 15:14:41 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		handle_decode(t_des *data, unsigned int len)
{
	unsigned int	last_i;
	unsigned char	last;

	data->strlen = len;
	last_i = len - 1;
	last = data->str[last_i];
	if (last <= 8)
	{
		while ((data->str[last_i] == last) && (len - last_i) <= last)
		{
			last_i--;
			data->strlen--;
		}
		if (len - last_i != last + 1)
			data->strlen = len;
	}
}

void			des_pad(t_des *data, unsigned int i, unsigned char *str)
{
	free(data->str);
	data->str = str;
	if (i <= 0)
		return ;
	if (data->decode)
		handle_decode(data, i);
}

void			des_pad_input(t_des *data)
{
	unsigned char	*padding;
	unsigned int	amount;
	unsigned int	i;

	if (!data->decode)
	{
		amount = 8 - (data->strlen % 8);
		padding = (unsigned char *)ft_strnew(amount);
		i = 0;
		while (i < amount)
			padding[i++] = amount;
		data->str = raw_append(data->str, padding, data->strlen, amount);
		data->strlen += amount;
	}
}
