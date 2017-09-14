/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_sbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:17 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 21:38:17 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

/*
** Input char should be 6 bits of data.
** Output char should be 4 bits of data.
*/

unsigned char	des_sbox(unsigned char sixbits, unsigned char *box)
{
	unsigned char	index;

	index = 0;
	index += ((sixbits >> 5) & 1) * 32;
	index += (sixbits & 1) * 16;
	index += ((sixbits >> 1) & 15);
	return (box[(int)index]);
}

/*
** Input should be an array of 6 chars * 8 bits
** 		48 bits total
** Output should be an array of 4 chars * 8 bits
** 		32 bits total
*/

unsigned char	*des_sbox_sub(unsigned char *six)
{
	unsigned char	*four;

	four = (unsigned char *)ft_strnew(4);
	if (!four)
		return (NULL);
	four[0] = des_sbox(six[0] >> 2, g_des_sbox_1) << 4;
	four[0] += des_sbox(((six[0] & 3) << 4) + (six[1] >> 4), g_des_sbox_2);
	four[1] = des_sbox(((six[1] & 15) << 2) + (six[2] >> 6), g_des_sbox_3) << 4;
	four[1] += des_sbox(six[2] & 63, g_des_sbox_4);
	four[2] = des_sbox(six[3] >> 2, g_des_sbox_5) << 4;
	four[2] += des_sbox(((six[3] & 3) << 4) + (six[4] >> 4), g_des_sbox_6);
	four[3] = des_sbox(((six[4] & 15) << 2) + (six[5] >> 6), g_des_sbox_7) << 4;
	four[3] += des_sbox(six[5] & 63, g_des_sbox_8);
	free(six);
	return (four);
}
