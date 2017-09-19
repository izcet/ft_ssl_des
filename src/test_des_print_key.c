/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_des_print_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:40:49 by irhett            #+#    #+#             */
/*   Updated: 2017/09/19 16:56:04 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

static void		print_byte(unsigned char c, int i)
{
	while (i-- > 0)
		ft_putstr("        ");
	printf("%i%i%i%i%i%i%i%i\n", (c & 128) >> 7, (c & 64) >> 6, (c & 32) >> 5, 
			(c & 16) >> 4, (c & 8) >> 3, (c & 4) >> 2, (c & 2) >> 1, c & 1);
}

void		test_des_print_key(unsigned char *eight)
{
	printf("KEY {\n");
	int 	i;

	i = 0;
	while (i < 8)
	{
		print_byte(eight[i], i);
		i++;
	}
	printf("}\n");
}

void		test_des_print_subkey(unsigned char *seven)
{
	printf("SUBKEY {\n");
	int 	i;

	i = 0;
	while (i < 7)
	{
		print_byte(seven[i], i);
		i++;
	}
	printf("}\n");
}

void		test_des_print_roundkey(unsigned char *six)
{
	printf("ROUNDKEY {\n");
	int 	i;

	i = 0;
	while (i < 6)
	{
		print_byte(six[i], i);
		i++;
	}
	printf("}\n");
}
