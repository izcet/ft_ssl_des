/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_perm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 15:09:14 by irhett            #+#    #+#             */
/*   Updated: 2017/09/19 15:37:07 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		perm_operate_init(unsigned char *bits, unsigned char c, char j)
{
	//printf("perm_operate_init(%s, %i, %i)\n", bits, c, j);
	char	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			bits[(int)i] = bits[(int)i] | (1 << j);
		i++;
	}
}

void			des_init_perm(unsigned char *eight)
{
	//printf("des_init_perm(%s)\n", eight);
	unsigned char	*bits;

	bits = (unsigned char[8]){0, 0, 0, 0, 0, 0, 0, 0};
	perm_operate_init(bits, eight[0], 6);
	perm_operate_init(bits, eight[1], 4);
	perm_operate_init(bits, eight[2], 2);
	perm_operate_init(bits, eight[3], 0);
	perm_operate_init(bits, eight[4], 7);
	perm_operate_init(bits, eight[5], 5);
	perm_operate_init(bits, eight[6], 3);
	perm_operate_init(bits, eight[7], 1);
	raw_copy(eight, bits, 8);
}

static void		perm_operate_final(unsigned char *b, unsigned char *e, char j)
{
	//printf("perm_operate_final(%s, %s, %i)\n", b, e, j);
	char	i;

	i = 0;
	while (i < 8)
	{
		if (e[(int)i] & (1 << j))
			*b = *b + (1 << i);
		i++;
	}
}

void			des_final_perm(unsigned char *eight)
{
	//printf("des_final_perm(%s)\n", eight);
	unsigned char	*bits;

	bits = (unsigned char[8]){0, 0, 0, 0, 0, 0, 0, 0};
	perm_operate_final(&(bits[0]), eight, 6);
	perm_operate_final(&(bits[1]), eight, 4);
	perm_operate_final(&(bits[2]), eight, 2);
	perm_operate_final(&(bits[3]), eight, 0);
	perm_operate_final(&(bits[4]), eight, 7);
	perm_operate_final(&(bits[5]), eight, 5);
	perm_operate_final(&(bits[6]), eight, 3);
	perm_operate_final(&(bits[7]), eight, 1);
	raw_copy(eight, bits, 8);
}
