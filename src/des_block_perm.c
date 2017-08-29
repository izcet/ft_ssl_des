/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_perm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 15:09:14 by irhett            #+#    #+#             */
/*   Updated: 2017/08/28 17:34:40 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		perm_operate_init(char *bits, char c, char index)
{
	char	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			bits[(int)i] = bits[(int)i] | (1 << index);
		i++;
	}
}

void			des_init_perm(char *eight)
{
	char	bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	perm_operate_init(bits, eight[0], 6);
	perm_operate_init(bits, eight[1], 4);
	perm_operate_init(bits, eight[2], 2);
	perm_operate_init(bits, eight[3], 0);
	perm_operate_init(bits, eight[4], 7);
	perm_operate_init(bits, eight[5], 5);
	perm_operate_init(bits, eight[6], 3);
	perm_operate_init(bits, eight[7], 1);
	ft_strncpy(eight, bits, 8);
}

static void		perm_operate_final(char *bits, char *eight, char index)
{
	char	i;

	i = 0;
	while (i < 8)
	{
		if (eight[(int)i] & (1 << index))
			*bits = *bits & (1 << i);
		i++;
	}
}

void			des_final_perm(char *eight)
{
	char	bits[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	perm_operate_final(&(bits[0]), eight, 6);
	perm_operate_final(&(bits[1]), eight, 4);
	perm_operate_final(&(bits[2]), eight, 2);
	perm_operate_final(&(bits[3]), eight, 0);
	perm_operate_final(&(bits[4]), eight, 7);
	perm_operate_final(&(bits[5]), eight, 5);
	perm_operate_final(&(bits[6]), eight, 3);
	perm_operate_final(&(bits[7]), eight, 1);
	ft_strncpy(eight, bits, 8);
}
