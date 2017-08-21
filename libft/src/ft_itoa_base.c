/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 15:07:39 by irhett            #+#    #+#             */
/*   Updated: 2017/06/23 00:03:13 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		number_len_base(unsigned int n, unsigned int base)
{
	unsigned int	len;

	len = 1;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	return (len);
}

char					*ft_itoa_base(int n, unsigned int base)
{
	char			*ans;
	char			*key;
	unsigned int	i;

	if (base == 10)
		return (ft_itoa(n));
	key = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	i = number_len_base(n, base);
	ans = ft_strnew(i--);
	while (n > 0)
	{
		ans[i] = key[n % base];
		n = n / base;
		if (i > 0)
			i--;
	}
	return (ans);
}
