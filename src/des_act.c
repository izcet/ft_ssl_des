/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_act.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 22:28:05 by irhett            #+#    #+#             */
/*   Updated: 2017/11/20 22:31:54 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define FREESET(foo, bar) free(foo); foo = bar

static t_output	*make_des_output(t_des *d)
{
	t_output	*o;

	o = (t_output *)malloc(sizeof(t_output));
	if (!o)
		return (NULL);
	o->com = d->c->name;
	o->file = d->outfile;
	o->str = (char *)d->str;
	o->strlen = d->strlen;
	if (d->base64 && !d->decode)
		o->newline = 1;
	else
		o->newline = 0;
	return (o);
}

int				des_act(t_des *d, t_com *c, void (*func)(t_des *))
{
	unsigned char	*temp;
	int				ret;

	ret = 0;
	func(d);
	if (d->base64 && !d->decode)
	{
		temp = base64_encode(d->str, BASE64_KEY, d->strlen);
		FREESET(d->str, temp);
		d->strlen = ft_strlen((char *)d->str);
	}
	if (d->outfile)
		ret = write_to_file(make_des_output(d));
	else
		write_to_stdout((char*)d->str, d->strlen, d->base64, d->decode);
	destroy_t_des(d);
	(void)c;
	return (ret);
}
