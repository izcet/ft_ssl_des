/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 21:48:26 by irhett            #+#    #+#             */
/*   Updated: 2017/09/11 21:49:37 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, unsigned int len)
{
	char	*dst;

	dst = ft_strnew(len);
	ft_strncpy(dst, src, len);
	return (dst);
}
