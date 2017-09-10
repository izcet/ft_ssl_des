/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 16:33:25 by irhett            #+#    #+#             */
/*   Updated: 2017/09/09 16:26:32 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

char	get_hex_val(char big, char smol)
{
	char	ret;

	ret = 0;
	if (ft_isdigit(smol))
		ret += (smol - '0');
	else
		ret += (10 + (ft_toupper(smol) - 'A'));
	if (ft_isdigit(big))
		ret += 16 * (big - '0');
	else
		ret += 16 * (10 + (ft_toupper(big) - 'A'));
	return (ret);
}
