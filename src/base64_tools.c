/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 14:53:54 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void			three_to_four(unsigned char *str, char *key,
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

int				four_to_three(unsigned char *str, unsigned char *enc, char *key)
{
	int				i;
	int				c_i;
	unsigned char	c[4];

	i = -1;
	while (++i < 4)
	{
		if (!(ft_isalpha(enc[i]) || ft_isdigit(enc[i]) || enc[i] == '+' ||
					enc[i] == '/' || enc[i] == '='))
			return (1);
	}
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
	return (0);
}

unsigned int	base64_trim(char *str)
{
	unsigned int	start;
	unsigned int	end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (!ft_isspace(str[end]))
		{
			str[start] = str[end];
			start++;
		}
		end++;
	}
	return (start);
}
