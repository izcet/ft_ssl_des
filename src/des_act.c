/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_act.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 22:28:05 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 22:35:25 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define FREESET(foo, bar) free(foo); foo = bar

int		des_act(t_des *d, t_com *c, void (*func)(t_des *))
{
	unsigned char	*temp;
	int				ret;

	ret = 0;
	if (d->decode && d->base64)
	{
		temp = base64_decode(d->str, BASE64_KEY, &(d->strlen), c->name);
		FREESET(d->str, temp);
	}
	func(d);
	if (d->base64 && !d->decode)
	{
		temp = base64_encode(d->str, BASE64_KEY, d->strlen);
		FREESET(d->str, temp);
		d->strlen = ft_strlen((char *)d->str);
	}
	if (d->outfile)
		ret = write_to_file((char *)d->str, d->outfile, c->name, d->strlen);
	else
		write(1, d->str, d->strlen);
	destroy_t_des(d);
	return (ret);
}
