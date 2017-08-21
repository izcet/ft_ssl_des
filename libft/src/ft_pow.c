/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 15:17:14 by irhett            #+#    #+#             */
/*   Updated: 2017/04/15 16:15:19 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_pow(unsigned int n, unsigned int exp)
{
	if (exp == 1)
		return (n);
	if (exp == 0)
		return (1);
	return (n * ft_pow(n, exp - 1));
}
