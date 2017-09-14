/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_xor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 21:14:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 21:46:37 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

unsigned char	*des_xor(unsigned char *str, unsigned char *other, int len)
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
