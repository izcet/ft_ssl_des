/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:14:30 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 22:58:50 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

/*
** Malloc's return value
** return value is length (l + r + 1) bzero'd
** copies l of str and r of new
** frees str and new
*/

unsigned char	*raw_append(unsigned char *str, unsigned char *new,
		unsigned int l, unsigned int r)
{
	unsigned char	*final;

	final = raw_expand(str, new, l, r);
	free(new);
	return (final);
}

unsigned char	*raw_clone(unsigned char *block, unsigned int len)
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

unsigned char	*raw_expand(unsigned char *str, unsigned char *new,
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
	return (final);
}

/*
** RAW XOR
** xor's STRING by OTHER, modifying LEN of STRING's characters
** OTHER is left alone
*/

void			raw_xor(unsigned char *str, unsigned char *o, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		str[i] = str[i] ^ o[i];
		i++;
	}
}

void			raw_copy(unsigned char *dst, unsigned char *src, unsigned int l)
{
	unsigned int	i;

	i = 0;
	while (i < l)
	{
		dst[i] = src[i];
		i++;
	}
}
