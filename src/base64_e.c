/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/15 16:59:11 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

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

unsigned char	*base64_decode(unsigned char *enc, char *key, unsigned int *len,
		char *caller)
{
	unsigned int	oldlen;
	unsigned int	i;
	unsigned char	*str;
	int				ret;

	oldlen = base64_trim((char *)enc);
	*len = (oldlen / 4) * 3;
	str = (unsigned char *)ft_strnew(*len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < *len)
	{
		ret = four_to_three(&(str[i]), enc, key);
		if (ret == -1)
		{
			com_err(caller, "Invalid character in input stream.");
			free(str);
			return (NULL);
		}
		i += 3;
		enc += 4;
	}
	*len -= ret;
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
			if (!d->decode)
				ft_putchar('\n');
		}
		free(string);
	}
	destroy_t_b64(d);
	return (ret);
}
