/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 22:03:50 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		three_to_four(unsigned char *str, char *key,
		unsigned char *enc, int num)
{
	int		i;
	int		past_done;

	i = 0;
	past_done = 0;
	enc[0] = key[(str[i++] & 252) >> 2];
	num--;
	enc[1] = key[((str[i - 1] & 3) << 4) | (str[i] >> 4)];
	if (!num)
		past_done = 1;
	if (num)
	{
		i++;
		num--;
	}
	enc[2] = past_done ? '=' : key[((str[i] & 192) >> 6) | ((str[i - 1] & 15) << 2)];
	if (!num)
		past_done = 1;
	enc[3] = past_done ? '=' : key[str[i] & 63];
}

unsigned char	*base64_encode(unsigned char *str, char *key, unsigned int len)
{
	unsigned int	i;
	unsigned int	ei;
	unsigned int	enc_len;
	unsigned char	*enc;

	enc_len = (((len + 2) / 3) * 4);
	enc = (unsigned char *)ft_strnew(enc_len);
	if (!enc)
		return (NULL);
	i = 0;
	ei = 0;
	while (ei < enc_len)
	{
		three_to_four(&(str[i]), key, &(enc[ei]), len - i);
		ei += 4;
		i += 3;
	}
	return (enc);
}

static void		four_to_three(unsigned char *str, unsigned char *enc, char *key)
{
	int				i;
	int				c_i;
	unsigned char	c[4];

	i = -1;
	while (++i < 64)
	{
		c_i = -1;
		while (++c_i < 4)
			if (enc[c_i] == key[i])
				c[c_i] = i;
	}
	i = -1;
	while (++i < 4)
		if (enc[i] == '=')
			c[i] = 0;
	str[0] = (c[0] << 2) | (c[1] >> 4);
	str[1] = ((c[1] & 15) << 4) | (c[2] >> 2);
	str[2] = ((c[2] & 3) << 6) | c[3];
}

unsigned char	*base64_decode(unsigned char *enc, char *key, unsigned int *len,
		char *caller)
{
	unsigned int	oldlen;
	unsigned int	i;
	unsigned char	*str;

	oldlen = ft_strlen((char *)enc);
	if (oldlen % 3 != 0)
	{
		com_err(caller, "bad input string length.");
		return (NULL);
	}
	*len = (oldlen / 4) * 3;
	str = (unsigned char *)ft_strnew(*len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < *len)
	{
		four_to_three(&(str[i]), enc, key);
		i += 3;
		enc += 4;
	}
	return (str);
}

int				base64_e(t_com *c, void *data_t_b64)
{
	t_b64			*d;
	unsigned char	*string;
	int				ret;

	d = (t_b64*)data_t_b64;
	if (d->decode)
		string = base64_decode(d->string, BASE64_KEY, &(d->strlen), c->name);
	else
	{
		string = base64_encode(d->string, BASE64_KEY, d->strlen);
		d->strlen = ft_strlen((char *)string);
	}
	ret = 0;
	if (string)
	{
		if (d->outfile)
			ret = write_to_file((char *)string, d->outfile, c->name, d->strlen);
		else
		{
			write(1, string, d->strlen);
			ft_putchar('\n');
		}
		free(string);
	}
	destroy_t_b64(d);
	return (ret);
}
