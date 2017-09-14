/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 21:14:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/14 10:02:04 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void	des_xor(unsigned char *str, unsigned char *other, unsigned int len)
{
	unsigned int		i;

	i = 0;
	while (i < len)
	{
		str[i] = str[i] ^ other[i];
		i++;
	}
}
