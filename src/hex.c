/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 16:33:25 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 22:09:00 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

/*
** This function assumes validation
** Non-zero ('\0') characters outside the range:
** 		'0' - '9' inclusive
** 		'A' - 'F' inclusive
** 		'a' - 'f' inclusive
** :will corrupt the return value
*/

unsigned char	get_hex_val(char big, char smol)
{
	unsigned char	ret;

	ret = 0;
	if (smol)
	{
		if (ft_isdigit(smol))
			ret += (smol - '0');
		else
			ret += (10 + (ft_toupper(smol) - 'A'));
	}
	if (big)
	{
		if (ft_isdigit(big))
			ret += (big - '0') << 4;
		else
			ret += (10 + (ft_toupper(big) - 'A')) << 4;
	}
	return (ret);
}

int		ft_ishex(char c)
{
	if (ft_isdigit(c))
		return (1);
	if ((c >= 'a') && (c <= 'f'))
		return (1);
	if ((c >= 'A') && (c <= 'F'))
		return (1);
	return (0);
}
