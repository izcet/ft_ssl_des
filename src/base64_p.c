/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:28:08 by irhett            #+#    #+#             */
/*   Updated: 2017/08/22 17:11:05 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

void		*base64_p(int argc, char **argv)
{
	printf("calling base64 parser\n");
	(void)argv;

	t_b64	*data;

	data = (t_b64*)malloc(sizeof(t_b64));
	if (!data)
		return (NULL);


	if (argc % 2)
	{
		free(data);
		return (NULL);
	}
	//printf("%p %p\n", data, (void*)data);
	return ((void *)data);
}
