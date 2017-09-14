/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key_perm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:19:48 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 11:24:35 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define LSHBY(a,b,c) ((eight[a] & b) << c)
#define RSHBY(a,b,c) ((eight[a] & b) >> c)

#define LSHKY(a,b,c) ((key[a] & b) << c)
#define RSHKY(a,b,c) ((key[a] & b) >> c)

#define GETKY(a,b) (key[a] & b)

/*
** Eigth bit is dropped from the original 64 bit key to form the 56 bit key
** Permuted against a table, not the code below (though saved for future ref)
** Seven Byte 56 bits is Malloc'd and returned
** Eight Bytes is left untouched and must be cleaned up in the calling process
*/

/*
**	char	*seven;
**	int		i;
**
**	seven = ft_strnew(7);
**	if (!seven)
**		return (NULL);
**	i = 0;
**	while (i < 7)
**	{
**		seven[i] = ((eight[i] & ~1) << i) + (eight[i + 1] >> (7 - i));
**		i++;
**	}
**	return (seven);
*/

/*
** j should be -1 when used here
*/

unsigned char	*des_key_reduction(unsigned char *eight, int j)
{
	printf("REDUCE!\n");
	unsigned char	*seven;
	int		i;

	seven = (unsigned char *)ft_strnew(7);
	if (!seven)
		return (NULL);
	while (++j < 3)
	{
		i = -1;
		while (++i < 8)
			seven[j] += (eight[7 - i] & (128 >> j)) >> i;
	}
	seven[3] += LSHBY(7, 16, 3) + LSHBY(6, 16, 2) + LSHBY(5, 16, 1);
	seven[3] += LSHBY(4, 16, 0) + LSHBY(7, 2, 2) + LSHBY(6, 2, 1);
	seven[3] += LSHBY(5, 2, 0) + RSHBY(4, 2, 1);
	seven[4] += LSHBY(3, 2, 6) + LSHBY(2, 2, 5) + LSHBY(1, 2, 4);
	seven[4] += LSHBY(0, 2, 3) + LSHBY(7, 4, 1) + LSHBY(6, 4, 0);
	seven[4] += RSHBY(5, 4, 1) + RSHBY(4, 4, 2);
	seven[5] += LSHBY(3, 4, 5) + LSHBY(2, 4, 4) + LSHBY(1, 4, 3);
	seven[5] += LSHBY(0, 4, 2) + RSHBY(7, 8, 0) + RSHBY(6, 8, 1);
	seven[5] += RSHBY(5, 8, 2) + RSHBY(4, 8, 3);
	seven[6] += LSHBY(3, 8, 4) + LSHBY(2, 8, 3) + LSHBY(1, 8, 2);
	seven[6] += RSHBY(0, 8, 1) + RSHBY(3, 16, 1) + RSHBY(2, 16, 2);
	seven[6] += RSHBY(1, 16, 3) + RSHBY(0, 16, 4);
	return (seven);
}

void			des_key_r_rot(unsigned char *key, int num)
{
	unsigned char	ltemp;
	unsigned char	rtemp;

	ltemp = (key[3] & ((3 << (2 + num)) & ~15)) << (4 - num);
	rtemp = (key[6] & (3 >> (2 - num))) << (4 - num);
	key[6] = (key[6] >> num) + (key[5] << (8 - num));
	key[5] = (key[5] >> num) + (key[4] << (8 - num));
	key[4] = (key[4] >> num) + (key[3] << (8 - num));
	key[3] = (key[3] >> num) + (key[2] << (8 - num));
	key[3] = (key[3] & ~((3 << (4 - num)) & 15)) + (rtemp);
	key[2] = (key[2] >> num) + (key[1] << (8 - num));
	key[1] = (key[1] >> num) + ltemp;
}

void			des_key_l_rot(unsigned char *key, int num)
{
	unsigned char	ltemp;
	unsigned char	rtemp;

	ltemp = (key[0] >> (8 - num)) << 4;
	rtemp = (key[3] & 15) >> (4 - num);
	key[0] = (key[0] << num) + (key[1] >> (8 - num));
	key[1] = (key[1] << num) + (key[2] >> (8 - num));
	key[2] = (key[2] << num) + (key[3] >> (8 - num));
	key[3] = (key[3] << num) + (key[4] >> (8 - num)); 
	key[3] = (key[3] & ~((3 << (num + 2)) & ~15)) + (ltemp);
	key[4] = (key[4] << num) + (key[5] >> (8 - num));
	key[5] = (key[5] << num) + (key[6] >> (8 - num));
	key[6] = (key[6] << num) + rtemp;
}

/*
** Input is 7 chars, 56 bytes
** Output is 6 chars, 48 bytes
*/

unsigned char	*des_get_subkey(unsigned char *key)
{
	unsigned char	*sub;

	sub = (unsigned char *)ft_strnew(6);
	if (!sub)
		return (NULL);
	sub[0] += LSHKY(1, 4, 5) + RSHKY(2, 128, 1) + GETKY(1, 32);
	sub[0] += LSHKY(2, 1, 4) + RSHKY(0, 128, 4) + RSHKY(0, 8, 1);
	sub[0] += RSHKY(0, 32, 4) + RSHKY(3, 16, 4);
	sub[1] += LSHKY(1, 2, 6) + LSHKY(0, 4, 4) + LSHKY(2, 8, 2);
	sub[1] += RSHKY(1, 64, 2) + LSHKY(2, 2, 2) + RSHKY(2, 16, 2);
	sub[1] += RSHKY(2, 16, 3) + RSHKY(0, 16, 4);
	sub[2] += LSHKY(3, 64, 1) + LSHKY(0, 1, 6) + LSHKY(1, 1, 4);
	sub[2] += LSHKY(0, 2, 3) + RSHKY(3, 32, 2) + RSHKY(2, 16, 2);
	sub[2] += RSHKY(1, 8, 2) + RSHKY(0, 64, 6);
	sub[3] += GETKY(5, 128) + LSHKY(6, 16, 2) + LSHKY(3, 2, 4);
	sub[3] += LSHKY(4, 8, 1) + LSHKY(5, 2, 2) + LSHKY(6, 2, 1);
	sub[3] += RSHKY(3, 4, 1) + GETKY(4, 1);
	sub[4] += LSHKY(6, 32, 2) + LSHKY(5, 8, 3) + RSHKY(4, 128, 2);
	sub[4] += LSHKY(5, 1, 4) + RSHKY(4, 16, 1) + RSHKY(6, 128, 5);
	sub[4] += GETKY(5, 2) + GETKY(6, 1);
	sub[5] += LSHKY(4, 64, 1) + LSHKY(6, 8, 3) + LSHKY(5, 4, 3);
	sub[5] += RSHKY(5, 64, 2) + RSHKY(6, 64, 3) + RSHKY(4, 16, 2);
	sub[5] += RSHKY(3, 8, 2) + GETKY(3, 1);
	return (sub);
}
