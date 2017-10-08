/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_des_print_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:40:49 by irhett            #+#    #+#             */
/*   Updated: 2017/10/07 23:00:40 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		print_byte(unsigned char c)
{
	ft_putchar('0' + ((c & 128) >> 7));
	ft_putchar('0' + ((c & 64) >> 6));
	ft_putchar('0' + ((c & 32) >> 5));
	ft_putchar('0' + ((c & 16) >> 4));
	ft_putchar('0' + ((c & 8) >> 3));
	ft_putchar('0' + ((c & 4) >> 2));
	ft_putchar('0' + ((c & 2) >> 1));
	ft_putchar('0' + (c & 1));
}

void			test_print_num(unsigned char *arr, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (i > 0)
			ft_putchar(' ');
		print_byte(arr[i]);
		i++;
	}
	ft_putchar('\n');
}

void			test_des_print_key(unsigned char *eight)
{
	test_print_num(eight, 8);
}

void			test_des_print_subkey(unsigned char *seven)
{
	test_print_num(seven, 7);
}

void			test_des_print_roundkey(unsigned char *six)
{
	test_print_num(six, 6);
}
