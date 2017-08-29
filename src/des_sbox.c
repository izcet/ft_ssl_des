/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_sbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:17 by irhett            #+#    #+#             */
/*   Updated: 2017/08/28 17:35:04 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

/*
** Input char should be 6 bits of data.
** Output char should be 4 bits of data.
*/

char	des_sbox_lookup(char sixbits, char *box)
{
	char	index;

	index = 0;
	index += ((sixbits >> 5) & 1) * 32;
	index += (sixbits & 1) * 16;
	index += ((sixbits >> 1) & 15);
	return (box[(int)index]);
}
