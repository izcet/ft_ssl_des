/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_sixteen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:14:30 by irhett            #+#    #+#             */
/*   Updated: 2017/09/11 20:26:34 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

char	*des_sixteen(char *message, char *key, int decode)
{
	int		i;
	char	*subkey;
	char	*left;
	char	*right;

	left = ft_strndup(message, 4);
	right = ft_strndup(message + 4, 4);
	i = 0;
	while (i < 16)
	{
		if (decode)
			des_key_r_rot(key, g_des_key_dec[i]);
		else
			des_key_l_rot(key, g_des_key_enc[i]);
		subkey = des_get_subkey(key);
		des_round(left, right, subkey);
		free(subkey);
		swap_ptr(left, right);
		i++;
	}
	return (gnl_concat(left, right, 1, 1));
}

char	*des_get_message(t_des *data)
{
	char			*first;
	char			*final;
	char			*temp_one;
	char			*temp_two;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	len = 0;
	first = read_data(data->infile, data->c->name, &len);
	if (data->decode && data->base64)
	{
		final = base64_decode(first, BASE64_KEY);
		free(first);
		first = final;
	}
	final = ft_strnew(0);
	i = 0;
	temp_one = ft_strnew(8);
	while (i < len)
	{
		j = 0;
		while ((j < 8) && (i + j < len))
		{
			temp_one[j] = first[i + j];
			j++;
		}
		while (j < 8)
			temp_one[j++] = '\0';
		i += j;
		if (data->iv)
			des_xor(temp_one, data->iv, 8);
		temp_two = des_sixteen(temp_one, data->key, data->decode);
		if (data->iv)
		{
			free(data->iv);
			data->iv = ft_strdup(temp_two);
		}
		final = gnl_concat(final, temp_two, 1, 1);
	}
	free(temp_one);
	free(first);
	if (data->base64 && !data->decode)
	{
		first = base64_encode(final, BASE64_KEY, i);
		free(final);
		final = first;
	}
	return (final);
}
