/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:32:54 by irhett            #+#    #+#             */
/*   Updated: 2017/09/13 21:36:16 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;
	str = (char*)malloc(sizeof(char) * (size + 1));
	i = 0;
	if (str)
	{
		while (i <= size)
			str[i++] = '\0';
	}
	return (str);
}
