/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/11/20 22:43:50 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void			three_to_four(unsigned char *str, char *key,
		unsigned char *enc, int num)
{
	int		i;
	int		done;

	i = 0;
	done = 0;
	enc[0] = key[(str[i++] & 252) >> 2];
	num--;
	enc[1] = key[((str[i - 1] & 3) << 4) | (str[i] >> 4)];
	if (!num)
		done = 1;
	if (num)
	{
		i++;
		num--;
	}
	enc[2] = done ? '=' : key[((str[i] & 192) >> 6) | ((str[i - 1] & 15) << 2)];
	if (!num)
		done = 1;
	enc[3] = done ? '=' : key[str[i] & 63];
}

static int		copy_over(unsigned char *c, unsigned char *e, unsigned char *s)
{
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	while (++i < 4)
		if (e[i] == '=')
		{
			ret++;
			c[i] = 0;
		}
	s[0] = (c[0] << 2) | (c[1] >> 4);
	s[1] = ((c[1] & 15) << 4) | (c[2] >> 2);
	s[2] = ((c[2] & 3) << 6) | c[3];
	return (ret);
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
			return (-1);
	}
	i = -1;
	while (++i < 64)
	{
		c_i = -1;
		while (++c_i < 4)
			if (enc[c_i] == key[i])
				c[c_i] = i;
	}
	return (copy_over(c, enc, str));
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
