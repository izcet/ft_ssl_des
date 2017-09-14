/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:14:30 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 16:47:08 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

unsigned char	*des_sixteen(unsigned char *block, unsigned char *key, int d)
{
	unsigned int		i;
	unsigned char	*subkey;
	unsigned char	*left;
	unsigned char	*right;

	left = raw_clone(block, 4);
	right = raw_clone(&(block[4]), 4);
	i = 0;
	while (i < 16)
	{
		if (d)
			des_key_r_rot(key, g_des_key_dec[i]);
		else
			des_key_l_rot(key, g_des_key_enc[i]);
		subkey = des_get_subkey(key);
		des_round(left, right, subkey);
		free(subkey);
		swap_ptr((void**)&left, (void**)&right);
		i++;
	}
	free(block);
	return (raw_append(left, right, 4, 4));
}

unsigned char	*des_work(t_des *data)
{
	unsigned char	*first;
	unsigned char	*final;
	unsigned char	*temp_one;
	unsigned char	*temp_two;
	unsigned char	*temp_key;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	len = 0;
	first = data->str; // no. bad
	temp_key = des_key_reduction(data->key, -1); //fix me
	final = (unsigned char *)ft_strnew(0);
	i = 0;
	while (i < len)
	{
		temp_one = (unsigned char *)ft_strnew(8);
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
		temp_two = des_sixteen(temp_one, temp_key, data->decode);
		if (data->iv)
		{
			free(data->iv);
			data->iv = raw_clone(temp_two, 8);
		}
		final = raw_append(final, temp_two, i - 8, 8);
	}
	free(first);
	free(temp_key);
	if (data->base64 && !data->decode)
	{
		first = base64_encode(final, BASE64_KEY, i);
		free(final);
		final = first;
		data->strlen = ft_strlen((char *)final);
	}
	else
		data->strlen = len;
	return (final);
}
