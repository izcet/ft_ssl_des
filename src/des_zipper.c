/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_zipper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 19:33:08 by irhett            #+#    #+#             */
/*   Updated: 2017/09/22 21:00:07 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

unsigned char	*des_get_left(unsigned char *block)
{
	int				i;
	int				j;
	int				k;
	unsigned char	*four;

	four = (unsigned char *)ft_strnew(4);
	i = 0;
	j = 0;
	while (j < 4)
	{
		k = 7;
		while (k > 0)
		{
			four[j] += ((block[i] >> k) & 1) << ((k / 2) + 4);
			k -= 2;
		}
		i++;
		k = 7;
		while (k > 0)
		{
			four[j] += ((block[i] >> k) & 1) << (k / 2);
			k -= 2;
		}
		i++;
		j++;
	}
	return (four);
}

unsigned char	*des_get_right(unsigned char *block)
{
	int				i;
	int				j;
	int				k;
	unsigned char	*four;

	four = (unsigned char *)ft_strnew(4);
	i = 0;
	j = 0;
	while (i < 8)
	{
		k = 6;
		while (k >= 0)
		{
			four[j] += ((block[i] >> k) & 1) << (((k + 1) / 2) + 4);
			k -= 2;
		}
		i++;
		k = 6;
		while (k >= 0)
		{
			four[j] += ((block[i] >> k) & 1) << ((k + 1) / 2);
			k -= 2;
		}
		i++;
		j++;
	}
	return (four);
}

unsigned char	*des_zipper(unsigned char *left, unsigned char *right)
{
	unsigned char	*block;
	int				i;
	int				j;

	test_print_num(left, 4);
	test_print_num(right, 4);
	block = (unsigned char *)ft_strnew(8);
	i = 0;
	while (i < 8)
	{
		j = (i % 2) ? 3 : 7;
		//printf("%i %i\n", i, j);
		while (j >= (4 - ((i % 2) * 4)))
		{
			block[i] += (left[i / 2] >> j) & 1;
			block[i] <<= 1;
			block[i] += (right[i / 2] >> j) & 1;
			if (j % 4)
				block[i] <<= 1;
			j--;
		}
		i++;
	}
	free(left);
	free(right);
	test_print_num(block, 8);
	return (block);
}
