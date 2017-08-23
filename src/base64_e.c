/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_e.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 16:37:49 by irhett            #+#    #+#             */
/*   Updated: 2017/08/22 17:11:10 by irhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftssl.h"

int			base64_e(t_com *command, void *data_t_b64)
{
	t_b64	*data;

	data = (t_b64*)data_t_b64;
	printf("calling base64 execution.\n");
	(void)command;
	//printf("%p %p\n", data_t_b64, data);
	free(data_t_b64);
	return (0);
}
