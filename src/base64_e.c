/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/09 20:04:59 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		three_to_four(char *str, char *key, char *enc)
{
	int		i;
	int		past_done;

	i = 0;
	past_done = 0;
	enc[0] = key[str[i++] >> 2];
	enc[1] = key[((str[i - 1] & 3) << 4) | (str[i] >> 4)];
	if (!str[i])
		past_done = 1;
	if (str[i])
		i++;
	enc[2] = past_done ? '=' : key[(str[i] >> 6) | ((str[i - 1] & 15) << 2)];
	if (!str[i])
		past_done = 1;
	enc[3] = past_done ? '=' : key[str[i] & 63];
}

char			*base64_encode(char *string, char *key)
{
	unsigned int	i;
	unsigned int	len;
	unsigned int	enc_i;
	unsigned int	enc_len;
	char			*encoded;

	i = 0;
	len = ft_strlen(string);
	enc_len = (((len + 2) / 3) * 4);
	encoded = ft_strnew(enc_len);
	if (!encoded)
		return (NULL);
	enc_i = 0;
	while (enc_i < enc_len)
	{
		three_to_four(&(string[i]), key, &(encoded[enc_i]));
		enc_i += 4;
		i += 3;
	}
	return (encoded);
}

static void		four_to_three(char *str, char *enc, char *key)
{
	int		i;
	int		c_i;
	char	c[4];

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

char			*base64_decode(char *encoded, char *key)
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	len = (ft_strlen(encoded) / 4) * 3;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		four_to_three(&(str[i]), encoded, key);
		i += 3;
		encoded += 4;
	}
	return (str);
}

int				base64_e(t_com *command, void *data_t_b64)
{
	t_b64	*data;
	char	*string;
	int		ret;

	data = (t_b64*)data_t_b64;
	if (data->decode)
		string = base64_decode(data->string, BASE64_KEY);
	else
		string = base64_encode(data->string, BASE64_KEY);
	ret = 0;
	if (data->outfile)
		ret = write_to_file(string, data->outfile, command->name);
	else
		ft_putendl(string);
	free(string);
	destroy_t_b64(data);
	return (ret);
}
