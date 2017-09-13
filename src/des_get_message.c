/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_get_message.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:14:30 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 01:02:39 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

char	*des_add_block(char *str, char *new, unsigned int l, unsigned int r)
{
	char			*final;
	unsigned int	i;

	final = ft_strnew(l + r);
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
	printf("here\n");
	free(str);
	printf("heren\n");
	free(new);
	return (final);
}

char	*clone_block(char *block, unsigned int len)
{
	char			*new;
	unsigned int	i;

	new = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		new[i] = block[i];
		i++;
	}
	return (new);
}

char	*des_sixteen(char *message, char *key, int decode)
{
	int		i;
	char	*subkey;
	char	*left;
	char	*right;

	left = clone_block(message, 4);
	printf("\nleft done\n");
	right = clone_block(message + 4, 4);
	printf("\nright done\n");
	i = 0;
	while (i < 16)
	{
		if (decode)
			des_key_r_rot((unsigned char *)key, g_des_key_dec[i]);
		else
			des_key_l_rot((unsigned char *)key, g_des_key_enc[i]);
		printf("%i\n", i);
		printf("a\n");
		subkey = des_get_subkey((unsigned char *)key);
		printf("b\n");
		des_round(left, right, subkey);
		printf("c\n");
		free(subkey);
		printf("d\n");
		swap_ptr(left, right);
		i++;
	}
	printf("foo\n");
	return (des_add_block(left, right, 4, 4));
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
		final = base64_decode(first, BASE64_KEY, &len, data->c->name);
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
		printf("%i\n", i);
		temp_two = des_sixteen(temp_one, data->key, data->decode);
		printf("%i\n", i);
		if (data->iv)
		{
			free(data->iv);
			data->iv = clone_block(temp_two, 8);
		}
		final = des_add_block(final, temp_two, i - 8, 8);
	}
	free(temp_one);
	free(first);
	if (data->base64 && !data->decode)
	{
		first = base64_encode(final, BASE64_KEY, i);
		free(final);
		final = first;
		data->strlen = ft_strlen(final);
	}
	else
		data->strlen = len;
	return (final);
}
