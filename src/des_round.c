/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_round.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:22:18 by irhett            #+#    #+#             */
/*   Updated: 2017/09/01 19:14:44 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static char		*des_xor(char *str, char *other, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str[i] = str[i] ^ other[i];
		i++;
	}
	return (str);
}

static char		*des_expansion_perm(char *right)
{

}

static char		*des_pbox_perm(char *str);
{

}

/*
** left		= 4 chars
** right	= 4 chars
** key		= 6 chars, subkey
** last		= 8 chars. NULL if ECB mode, otherwise CBC
*/

/*
** right must remain untouched
** temporary string contains right's workings
** left is modified by xor with temp to become the new right
*/

void	des_round(char *left, char *right char *key)
{
	char	*temp;

	temp = des_expansion_perm(right);
	temp = des_xor(temp, key, 6);
	temp = des_sbox_sub(temp);
	temp = des_pbox_perm(temp);
	left = des_xor(left, temp, 4);
	free(temp);
}
