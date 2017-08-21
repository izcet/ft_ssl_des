/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 23:14:00 by irhett            #+#    #+#             */
/*   Updated: 2017/06/22 23:19:28 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_numlen(int num, int base)
{
	unsigned int	len;

	len = 1;
	if (num < 0)
	{
		len++;
		num = num - (num % base);
		num *= -1;
	}
	while (num >= base)
	{
		num /= base;
		len++;
	}
	return (len);
}
