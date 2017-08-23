/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/08/23 03:41:43 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define KEY64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

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

static char		*base64_encode(char *string, char *key)
{
	unsigned int	i;
	unsigned int	len;
	unsigned int	enc_i;
	unsigned int	enc_len;
	char			*encoded;

	i = 0;
	len = ft_strlen(string);
	enc_len = (((len + 2) / 3) * 4);
	encoded = (char *)malloc(sizeof(char) * (enc_len + 1));
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

static char		*base64_decode(char *string, char *key)
{
	(void)string;
	(void)key;
	return (NULL);
}

int				base64_e(t_com *command, void *data_t_b64)
{
	t_b64	*data;
	char	*string;
	int		ret;
	char	*key;

	data = (t_b64*)data_t_b64;
	key = ft_strdup(KEY64);
	if (data->decode)
		string = base64_decode(data->string, key);
	else
		string = base64_encode(data->string, key);
	ret = 0;
	if (data->outfile)
		ret = write_to_file(string, data->outfile, command->name);
	else
		ft_putendl(string);
	free(key);
	free(string);
	destroy_t_b64(data);
	return (ret);
}
