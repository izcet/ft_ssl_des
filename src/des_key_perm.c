/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key_perm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:19:48 by irhett            #+#    #+#             */
/*   Updated: 2017/09/03 18:51:01 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

#define LSHBY(a,b,c) ((eight[a] & b) << c)
#define RSHBY(a,b,c) ((eight[a] & b) >> c)

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

char	*des_key_init(char *eight)
{
	char	*seven;
	int		i;
	int		j;

	seven = ft_strnew(7);
	if (!seven)
		return (NULL);
	j = -1;
	while (++j < 3)
	{
		i = -1;
		while (++i < 8)
			seven[j] += (eight[7 - i] & (128 >> j)) >> i;
	}
	seven[3] += LSHBY(7,16,3) + LSHBY(6,16,2) + LSHBY(5,16,1) + LSHBY(4,16,0);
	seven[3] += LSHBY(7,2,2) + LSHBY(6,2,1) + LSHBY(5,2,0) + RSHBY(4,2,1);
	seven[4] += LSHBY(3,2,6) + LSHBY(2,2,5) + LSHBY(1,2,4) + LSHBY(0,2,3);
	seven[4] += LSHBY(7,4,1) + LSHBY(6,4,0) + RSHBY(5,4,1) + RSHBY(4,4,2);
	seven[5] += LSHBY(3,4,5) + LSHBY(2,4,4) + LSHBY(1,4,3) + LSHBY(0,4,2);
	seven[5] += RSHBY(7,8,0) + RSHBY(6,8,1) + RSHBY(5,8,2) + RSHBY(4,8,3);
	seven[6] += LSHBY(3,8,4) + LSHBY(2,8,3) + LSHBY(1,8,2) + RSHBY(0,8,1);
	seven[6] += RSHBY(3,16,1) + RSHBY(2,16,2) + RSHBY(1,16,3) + RSHBY(0,16,4);
	return (seven);

}

char	*rotate_key_right(char *key, int num)
{


}

char	*rotate_key_left(char *key, int num)
{

}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
