/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_perm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 15:09:14 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 22:58:01 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static unsigned char	set_init_byte(unsigned char *eight, unsigned char pos)
{
	int				i;
	unsigned char	byte;

	i = 0;
	byte = 0;
	while (i < 8)
	{
		byte += ((eight[i] & (1 << pos)) >> pos) << i;
		i++;
	}
	return (byte);
}

void					des_init_perm(unsigned char *eight)
{
	unsigned char	*bits;

	bits = (unsigned char[8]){0, 0, 0, 0, 0, 0, 0, 0};
	bits[0] = set_init_byte(eight, 6);
	bits[1] = set_init_byte(eight, 4);
	bits[2] = set_init_byte(eight, 2);
	bits[3] = set_init_byte(eight, 0);
	bits[4] = set_init_byte(eight, 7);
	bits[5] = set_init_byte(eight, 5);
	bits[6] = set_init_byte(eight, 3);
	bits[7] = set_init_byte(eight, 1);
	raw_copy(eight, bits, 8);
}

static unsigned char	set_final_byte(unsigned char *eight, unsigned int row)
{
	unsigned char	byte;

	byte = 0;
	byte += ((eight[4] & (1 << row)) >> row) << 7;
	byte += ((eight[0] & (1 << row)) >> row) << 6;
	byte += ((eight[5] & (1 << row)) >> row) << 5;
	byte += ((eight[1] & (1 << row)) >> row) << 4;
	byte += ((eight[6] & (1 << row)) >> row) << 3;
	byte += ((eight[2] & (1 << row)) >> row) << 2;
	byte += ((eight[7] & (1 << row)) >> row) << 1;
	byte += ((eight[3] & (1 << row)) >> row);
	return (byte);
}

void					des_final_perm(unsigned char *eight)
{
	unsigned char	*bytes;
	int				i;

	bytes = (unsigned char[8]){0, 0, 0, 0, 0, 0, 0, 0};
	i = 0;
	while (i < 8)
	{
		bytes[i] = set_final_byte(eight, i);
		i++;
	}
	raw_copy(eight, bytes, 8);
}
