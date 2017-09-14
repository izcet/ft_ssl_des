/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_work.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:14:30 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 11:39:44 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

unsigned char	*des_add_block(unsigned char *str, unsigned char *new, 
		unsigned int l, unsigned int r)
{
	unsigned char	*final;
	unsigned int	i;

	final = (unsigned char *)ft_strnew(l + r);
	i = 0;
	while (i < l)
	{
		final[i] = str[i];
		i++;
	}
	i = 0;
	while (i < r)
	{
		final[i + l] = new[i];
		i++;
	}
	free(str);
	free(new);
	return (final);
}

unsigned char	*clone_block(unsigned char *block, unsigned int len)
{
	unsigned char	*new;
	unsigned int	i;

	new = (unsigned char *)ft_strnew(len);
	i = 0;
	while (i < len)
	{
		new[i] = block[i];
		i++;
	}
	return (new);
}

unsigned char	*des_sixteen(unsigned char *block, unsigned char *key, int d)
{
	unsigned int		i;
	unsigned char	*subkey;
	unsigned char	*left;
	unsigned char	*right;

	left = clone_block(block, 4);
	right = clone_block(&(block[4]), 4);
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
	return (des_add_block(left, right, 4, 4));
}

unsigned char	*des_work(t_des *data)
{
	unsigned char	*first;
	unsigned char	*final;
	unsigned char	*temp_one;
	unsigned char	*temp_two;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	printf("Starting get message\n");
	printf("{\nDecode: %i\nBase64: %i\nIF: %p - [%s]\nOF: %p - [%s]\nKY: %p - [%s]\nKY: %i\nV: %i\nIV: %p - [%s]\nCM: %p\nSTRLEN: %i\n", data->decode, data->base64, data->infile, data->infile, data->outfile, data->outfile, data->key, data->key, data->keylen, data->v, data->iv, data->iv, data->c, data->strlen);
	len = 0;
	first = read_data(data->infile, data->c->name, &len);
	printf("%s %i\n", first, len);
	data->key = des_key_reduction(data->key, -1); //fix me
	if (data->decode && data->base64)
	{
		final = base64_decode(first, BASE64_KEY, &len, data->c->name);
		free(first);
		first = final;
	}
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
		printf("\\ %i, \\ %i\n", i, j);
		while (j < 8)
			temp_one[j++] = '\0';
		i += j;
		printf("%i %i\n", i, j);
		if (data->iv)
			des_xor(temp_one, data->iv, 8);
		printf("%s\n", temp_one);
		temp_two = des_sixteen(temp_one, data->key, data->decode);
		if (data->iv)
		{
			free(data->iv);
			data->iv = clone_block(temp_two, 8);
		}
		final = des_add_block(final, temp_two, i - 8, 8);
	}
//	free(temp_one);
	free(first);
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
